// Controlled ablation of implementation choices, in C++.
// Fast (grid-binned, O(N)/step) reimplementation faithful to the original C++ SEIRS ABM:
//   20000 agents on a 300x300 toroidal grid, 20 initially infected, beta=0.5,
//   exponential residence times (mean 3/7/365), Moore neighbourhood incl. own cell,
//   infection p = 1 - exp(-beta * N_I), daily random relocation, 730 steps.
// One choice is varied at a time via command-line flags; the baseline reproduces the
// original C++ configuration.
//
// Flags:  argv[1]=rounding {floor|round|ceil|cont}   (baseline: floor)
//         argv[2]=order    {infect_move|move_infect}  (baseline: infect_move)
//         argv[3]=thresh   {gt|ge}                    (baseline: gt, i.e. elapsed > d)
//         argv[4]=redraw   {fixed|redraw}             (baseline: fixed)
//         argv[5]=nreps    (default 30)
//         argv[6]=seed0    (default 1)
//         argv[7]=update   {sync|async}                (baseline: sync)
#include <bits/stdc++.h>
using namespace std;

static const int SIZE=300, N=20000, I0=20, STEPS=730, PEAKWIN=150;
static const double BETA=0.5, TE=3.0, TI=7.0, TR=365.0;
enum {S=0,E=1,I=2,R=3};

int roundmode=0;      // 0 floor,1 round,2 ceil,3 continuous
bool order_infect_first=true;
bool thresh_gt=true;  // true: elapsed>d ; false: elapsed>=d
bool redraw=false;
bool asyncMode=false;     // true: update agents in random order, state visible within step

double drawExp(mt19937_64&g,double mean){
    uniform_real_distribution<double> u(0.0,1.0);
    double x = -mean*log(1.0-u(g));            // exponential
    if(roundmode==0) return floor(x);
    if(roundmode==1) return round(x);
    if(roundmode==2) return ceil(x);
    return x;                                   // continuous
}

// returns first-peak amplitude (count) and its day, via out params
void run(uint64_t seed, double&peakAmp, int&peakDay){
    mt19937_64 g(seed);
    vector<int> st(N,S), pos(N);
    vector<double> el(N,0.0), dE(N), dI(N), dR(N);
    uniform_int_distribution<int> cell(0,SIZE*SIZE-1);
    uniform_real_distribution<double> u(0.0,1.0);
    for(int k=0;k<N;k++){ dE[k]=drawExp(g,TE); dI[k]=drawExp(g,TI); dR[k]=drawExp(g,TR); pos[k]=cell(g); }
    for(int k=N-I0;k<N;k++) st[k]=I;

    vector<int> inf(SIZE*SIZE), neigh(SIZE*SIZE);
    peakAmp=0; peakDay=0;
    auto build_neigh=[&](){
        fill(inf.begin(),inf.end(),0);
        for(int k=0;k<N;k++) if(st[k]==I) inf[pos[k]]++;
        fill(neigh.begin(),neigh.end(),0);
        for(int x=0;x<SIZE;x++)for(int y=0;y<SIZE;y++){
            int s=0;
            for(int dx=-1;dx<=1;dx++)for(int dy=-1;dy<=1;dy++){
                int nx=(x+dx+SIZE)%SIZE, ny=(y+dy+SIZE)%SIZE;
                s+=inf[nx*SIZE+ny];
            }
            neigh[x*SIZE+y]=s;
        }
    };
    auto relocate=[&](){ for(int k=0;k<N;k++) pos[k]=cell(g); };
    auto ge=[&](double a,double b){ return thresh_gt ? (a>b) : (a>=b); };

    vector<int> ord(N); for(int k=0;k<N;k++) ord[k]=k;
    auto ninf=[&](int p){ int x=p/SIZE,y=p%SIZE,s=0;      // live 9-cell Moore infected count
        for(int dx=-1;dx<=1;dx++)for(int dy=-1;dy<=1;dy++){int nx=(x+dx+SIZE)%SIZE,ny=(y+dy+SIZE)%SIZE; s+=inf[nx*SIZE+ny];} return s; };
    auto do_transitions_and_infection=[&](){
        if(!asyncMode){                                        // SYNCHRONOUS: start-of-step snapshot
            build_neigh();
            for(int k=0;k<N;k++){
                if(st[k]==S){ int NI=neigh[pos[k]]; if(NI>0 && u(g)<1.0-exp(-BETA*NI)){ st[k]=E; el[k]=0;
                        if(redraw){dE[k]=drawExp(g,TE);dI[k]=drawExp(g,TI);dR[k]=drawExp(g,TR);} } else el[k]=0; }
                else if(st[k]==E){ if(ge(el[k],dE[k])){st[k]=I; el[k]=0;} else el[k]+=1; }
                else if(st[k]==I){ if(ge(el[k],dI[k])){st[k]=R; el[k]=0;} else el[k]+=1; }
                else { if(ge(el[k],dR[k])){st[k]=S; el[k]=0;} else el[k]+=1; }
            }
        } else {                                           // ASYNCHRONOUS: random order, live grid
            fill(inf.begin(),inf.end(),0);
            for(int k=0;k<N;k++) if(st[k]==I) inf[pos[k]]++;
            shuffle(ord.begin(),ord.end(),g);
            for(int idx=0; idx<N; idx++){ int k=ord[idx];
                if(st[k]==S){ int NI=ninf(pos[k]); if(NI>0 && u(g)<1.0-exp(-BETA*NI)){ st[k]=E; el[k]=0;
                        if(redraw){dE[k]=drawExp(g,TE);dI[k]=drawExp(g,TI);dR[k]=drawExp(g,TR);} } else el[k]=0; }
                else if(st[k]==E){ if(ge(el[k],dE[k])){st[k]=I; el[k]=0; inf[pos[k]]++;} else el[k]+=1; }
                else if(st[k]==I){ if(ge(el[k],dI[k])){st[k]=R; el[k]=0; inf[pos[k]]--;} else el[k]+=1; }
                else { if(ge(el[k],dR[k])){st[k]=S; el[k]=0;} else el[k]+=1; }
            }
        }
    };

    for(int t=0;t<STEPS;t++){
        int cI=0; for(int k=0;k<N;k++) if(st[k]==I) cI++;
        if(t<PEAKWIN && cI>peakAmp){ peakAmp=cI; peakDay=t; }
        if(order_infect_first){ do_transitions_and_infection(); relocate(); }
        else { relocate(); do_transitions_and_infection(); }
    }
}

int main(int argc,char**argv){
    string rm = argc>1?argv[1]:"floor";
    string od = argc>2?argv[2]:"infect_move";
    string th = argc>3?argv[3]:"gt";
    string rd = argc>4?argv[4]:"fixed";
    string up = argc>7?argv[7]:"sync";
    int nreps = argc>5?atoi(argv[5]):30;
    uint64_t seed0 = argc>6?strtoull(argv[6],0,10):1;
    roundmode = rm=="round"?1: rm=="ceil"?2: rm=="cont"?3:0;
    order_infect_first = (od!="move_infect");
    thresh_gt = (th!="ge");
    redraw = (rd=="redraw");
    asyncMode = (up=="async");

    double sAmp=0,sAmp2=0,sDay=0;
    for(int r=0;r<nreps;r++){ double a; int d; run(seed0+r,a,d); sAmp+=a; sAmp2+=a*a; sDay+=d; }
    double mA=sAmp/nreps, sdA=sqrt(max(0.0,sAmp2/nreps-mA*mA)), mD=sDay/nreps;
    printf("%-11s %-12s %-3s %-7s %-6s | reps=%d  peak_mean=%.0f  peak_sd=%.0f  day_mean=%.1f\n",
           rm.c_str(),od.c_str(),th.c_str(),rd.c_str(),up.c_str(),nreps,mA,sdA,mD);
    return 0;
}
