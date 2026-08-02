
class Monitor():
	def __init__(self, agents_count, model):
		self.model = model
		self.agents_count = agents_count
		self.results = {'t': [], 'S': [], 'E': [], 'I': [], 'R': []}
		self.update_results(0)

	def update_results(self, t):
		s = 0
		e = 0
		i = 0
		r = 0

		for agent in self.model.agents:
			status = agent.state["Status"]

			if (status == 'S'):
				s = s+1
			elif (status == 'E'):
				e = e+1
			elif (status == 'I'):
				i = i+1
			elif (status == 'R'):
				r = r+1

		self.results['t'].append(t)
		self.results['S'].append(s)
		self.results['E'].append(e)
		self.results['I'].append(i)
		self.results['R'].append(r)

	def get_results(self):
		return self.results

	def get_normalized_results(self):
		resS = []
		resE = []
		resI = []
		resR = []

		for i in range(0, len(self.results['t'])):
			resS.append(self.results['S'][i]/self.agents_count)
			resE.append(self.results['E'][i]/self.agents_count)
			resI.append(self.results['I'][i]/self.agents_count)
			resR.append(self.results['R'][i]/self.agents_count)

		return (self.results['t'], resS, resE, resI, resR)

	def export_results(self, save_file):
		(t, resS, resE, resI, resR) = self.get_normalized_results()

		save_file.write("timestamp,S,E,I,R\n")

		for i in range(0, len(self.results['t'])):
			save_file.write(str(t[i]))
			save_file.write(',')
			save_file.write(str(resS[i]))
			save_file.write(',')
			save_file.write(str(resE[i]))
			save_file.write(',')
			save_file.write(str(resI[i]))
			save_file.write(',')
			save_file.write(str(resR[i]))
			save_file.write('\n')