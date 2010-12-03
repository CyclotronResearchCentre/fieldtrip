#ifndef __SignalConfiguration_h
#define __SignalConfiguration_h

#include <vector>
#include <string>

struct ChannelSelection {
	std::vector<int> index;
	std::vector<std::string> label;
	
	bool parseString(int len, const char *str);
	
	void clear() {
		index.clear();
		label.clear();
	}
	
	void add(int newIndex, const char *newLabel) {
		index.push_back(newIndex);
		label.push_back(newLabel);
	}
	
	int getSize() const {
		return index.size();
	}
	
	int getIndex(int n) const {
		return index[n];
	}
	
	const char *getLabel(unsigned int n) const {
		return label[n].c_str();
	}
	
	static ChannelSelection selectByLabel(const ChannelSelection& sel, const ChannelSelection& all) {
		ChannelSelection cs;
		for (unsigned int i=0;i<sel.index.size();i++) {
			for (unsigned int j=0;j<all.index.size();j++) {
				if (sel.label[i].compare(all.label[j]) == 0) {
					cs.index.push_back(all.index[j]);
					cs.label.push_back(all.label[j]);
					break;
				}
			}
		}
		return cs;
	}
};

class SignalConfiguration {
	public:
	
	SignalConfiguration() : chanSelSave(), chanSelStream(), 
							downSample(1), maxChanSave(0), maxChanStream(0), 
							order(4), bandwidth(-1.0),
							batteryRefresh(10), statusRefresh(2) {};
	~SignalConfiguration() {};
	
	/** Parse given configuration file for options, returns number of errors */
	int parseFile(const char *filename);
	bool selectChannels(const char *str);
	bool setDownsampling(int factor) {
		if (factor < 1) return false;
		downSample = factor;
		return true;
	}
	
	void setBandwidth(double bandwidth) {
		this->bandwidth=bandwidth;
	}
	
	void setOrder(int order) {
		if (order>0) {
			this->order = order;
		}
	}

	int getDownsampling() const { return downSample; }
	double getBandwidth() const { return bandwidth; }
	int getOrder() const { return order; }
	int getBatteryRefresh() const { return batteryRefresh; }
	int getStatusRefresh() const { return statusRefresh; }
	int getMaxSavingChannel() const { return maxChanSave; }
	int getMaxStreamingChannel() const { return maxChanStream; }
	bool useSplittedTrigger() const { return splitTrigger; }
	const char *getLowTriggerName() const { return lowTriggerName.c_str(); }
	const char *getHighTriggerName() const { return highTriggerName.c_str(); }
	
	const ChannelSelection& getSavingSelection() const { return chanSelSave; }
	const ChannelSelection& getStreamingSelection() const { return chanSelStream; }
	
	protected:

	std::string lowTriggerName, highTriggerName;
	bool splitTrigger;
	ChannelSelection chanSelSave;
	ChannelSelection chanSelStream;
	int downSample;
	int maxChanSave;
	int maxChanStream;
	int order;
	double bandwidth;
	int batteryRefresh, statusRefresh;
};

#endif
