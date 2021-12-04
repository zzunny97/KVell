#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
using namespace std;

void print(vector<int>& v) {
	for(int a : v) cout << a << " ";
	cout << "\n";
}

vector<string> split(string s, string divid) {
	vector<string> v;
	char* c = strtok((char*)s.c_str(), divid.c_str());
	while (c) {
		v.push_back(c);
		c = strtok(NULL, divid.c_str());
	}
	return v;
}

int main(int argc, char** argv) {
	if(argc != 2) {
		cerr << "argument\n";
		exit(-1);
	}
	if(strcmp(argv[1], "abc") == 0) {
		vector<int> load_a_throughput;
		vector<int> ua_throughput, ua_latency_avg, ua_latency_99, ua_latency_max;
		vector<int> ub_throughput, ub_latency_avg, ub_latency_99, ub_latency_max;
		vector<int> uc_throughput, uc_latency_avg, uc_latency_99, uc_latency_max;
		vector<int> za_throughput, za_latency_avg, za_latency_99, za_latency_max;
		vector<int> zb_throughput, zb_latency_avg, zb_latency_99, zb_latency_max;
		vector<int> zc_throughput, zc_latency_avg, zc_latency_99, zc_latency_max;
		for(int i=1; i<=9; i++) {
			string path = "./data/"+to_string(i)+":"+to_string(10-i);
			ifstream in(path);		
			vector<int> tmp, tmp2;
			for(string line; getline(in, line); ) {
				if(line.find("Repopulating 10") != string::npos) {
					//cout << line << "\n";
					vector<string> toks = split(line, " ");					
					for(int i=0; i<toks.size(); i++) {
						if(toks[i] == "req/s)") {
							load_a_throughput.push_back(stoi(toks[i-1].substr(1)));
						}
					}
				}
				else if(line.find("req/s") != string::npos) {
					//cout << line << endl;
					vector<string> toks = split(line, " ");					
					for(int i=0; i<toks.size(); i++) {
						if(toks[i] == "req/s)") {
							tmp.push_back(stoi(toks[i-1].substr(1)));
						}
					}
				}
				else if(line.find("us") != string::npos) {
					//cout << line << endl;
					vector<string> toks = split(line, " ");					
					for(int i=0; i<toks.size(); i++) {
						if(toks[i] == "us") {
							tmp2.push_back(stoi(toks[i-1]));
						}
					}
				}
			}
			ua_throughput.push_back(tmp[0]);	
			ub_throughput.push_back(tmp[1]);	
			uc_throughput.push_back(tmp[2]);	
			za_throughput.push_back(tmp[3]);	
			zb_throughput.push_back(tmp[4]);	
			zc_throughput.push_back(tmp[5]);	

			ua_latency_avg.push_back(tmp2[0]);
			ua_latency_99.push_back(tmp2[1]);
			ua_latency_max.push_back(tmp2[2]);
			ub_latency_avg.push_back(tmp2[3]);
			ub_latency_99.push_back(tmp2[4]);
			ub_latency_max.push_back(tmp2[5]);
			uc_latency_avg.push_back(tmp2[6]);
			uc_latency_99.push_back(tmp2[7]);
			uc_latency_max.push_back(tmp2[8]);

			za_latency_avg.push_back(tmp2[9]);
			za_latency_99.push_back(tmp2[10]);
			za_latency_max.push_back(tmp2[11]);
			zb_latency_avg.push_back(tmp2[12]);
			zb_latency_99.push_back(tmp2[13]);
			zb_latency_max.push_back(tmp2[14]);
			zc_latency_avg.push_back(tmp2[15]);
			zc_latency_99.push_back(tmp2[16]);
			zc_latency_max.push_back(tmp2[17]);
		}
		cout << "Load A throughput (ops/s)\n";
		print(load_a_throughput);
		cout << "\n";
		cout << "Uniform A\n";
		print(ua_throughput);
		print(ua_latency_avg);
		print(ua_latency_99);
		print(ua_latency_max);
		cout << "\n";
		cout << "Unifom B\n";
		print(ub_throughput);
		print(ub_latency_avg);
		print(ub_latency_99);
		print(ub_latency_max);
		cout << "\n";
		cout << "Uniform C\n";
		print(uc_throughput);
		print(uc_latency_avg);
		print(uc_latency_99);
		print(uc_latency_max);
		cout << "\n";

		cout << "Zipfian A\n";
		print(za_throughput);
		print(za_latency_avg);
		print(za_latency_99);
		print(za_latency_max);
		cout << "\n";
		cout << "Zipfian B\n";
		print(zb_throughput);
		print(zb_latency_avg);
		print(zb_latency_99);
		print(zb_latency_max);
		cout << "\n";
		cout << "Zipfian C\n";
		print(zc_throughput);
		print(zc_latency_avg);
		print(zc_latency_99);
		print(zc_latency_max);
	}
	else if(strcmp(argv[1], "e") == 0) {
		vector<int> load_e_throughput;
		vector<int> ue_throughput, ue_latency_avg, ue_latency_99, ue_latency_max;
		vector<int> ze_throughput, ze_latency_avg, ze_latency_99, ze_latency_max;

		for(int i=1; i<=9; i++) {
			string path = "./data/"+to_string(i)+":"+to_string(10-i);
			ifstream in(path);		
			vector<int> tmp, tmp2;
			for(string line; getline(in, line); ) {
				if(line.find("Repopulating 10") != string::npos) {
					//cout << line << "\n";
					vector<string> toks = split(line, " ");					
					for(int i=0; i<toks.size(); i++) {
						if(toks[i] == "req/s)") {
							load_e_throughput.push_back(stoi(toks[i-1].substr(1)));
						}
					}
				}
				else if(line.find("req/s") != string::npos) {
					//cout << line << endl;
					vector<string> toks = split(line, " ");					
					for(int i=0; i<toks.size(); i++) {
						if(toks[i] == "req/s)") {
							tmp.push_back(stoi(toks[i-1].substr(1)));
						}
					}
				}
				else if(line.find("us") != string::npos) {
					//cout << line << endl;
					vector<string> toks = split(line, " ");					
					for(int i=0; i<toks.size(); i++) {
						if(toks[i] == "us") {
							tmp2.push_back(stoi(toks[i-1]));
						}
					}
				}
			}
			ue_throughput.push_back(tmp[0]);	
			ze_throughput.push_back(tmp[1]);	

			ue_latency_avg.push_back(tmp2[0]);
			ue_latency_99.push_back(tmp2[1]);
			ue_latency_max.push_back(tmp2[2]);

			ze_latency_avg.push_back(tmp2[3]);
			ze_latency_99.push_back(tmp2[4]);
			ze_latency_max.push_back(tmp2[5]);
		}
			cout << "Load E throughput (ops/s)\n";
			print(load_e_throughput);
			cout << "\n";
			cout << "Uniform E\n";
			print(ue_throughput);
			print(ue_latency_avg);
			print(ue_latency_99);
			print(ue_latency_max);
			cout << "\n";
			cout << "Zipfian E\n";
			print(ze_throughput);
			print(ze_latency_avg);
			print(ze_latency_99);
			print(ze_latency_max);
	}
	else {
		cerr << "argument\n";
		exit(-1);
	}


}
