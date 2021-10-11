#include <iostream>
#include <vector>
#include <cmath>
#include "pugixml.cpp"

using namespace std;

class Trans {
public:
	string num;
	string Type_of_vehicle;
	vector <string> Location;
	vector <string> Routes;
	double _X; double _Y;
};

void most_station_route_num(const vector<Trans> system, string transport_type) {
	vector<string> routes;
	vector<int> amount;
	for (int i = 0; i < system.size(); i++) {
		if (system[i].Type_of_vehicle == transport_type){
			
			for (int j = 0; j < system[i].Routes.size(); j++) {
				if (std::find(routes.begin(), routes.end(), system[i].Routes[j]) == routes.end()) {
					routes.push_back(system[i].Routes[j]);
						amount.push_back(0);
			}
		}
}
	}

	for (int i = 0; i < routes.size(); i++) {
		for (int j = 0; j < system.size(); j++) {
			if (std::find(system[j].Routes.begin(), system[j].Routes.end(), routes[i]) != system[j].Routes.end())
				amount[i]++;
		}
	}

	for (int i = 0; i < routes.size(); i++) {
		cout << routes[i] << " " << amount[i]<<"\t";
	}

	int max = 0, iter=0;
	for (int i = 0; i < amount.size(); i++) {
		if (amount[i] > max) {
			max = amount[i]; iter = i;
		}
	}
	cout <<routes[iter] << " " << max << "!!!!!!!!!!!!!!!!!!!!";
}

void longest_route_num(vector<Trans> system, string transport_type) {

}

void most_stop_num(vector<Trans> system) {

}

int main()
{
	setlocale(LC_ALL, "Russian");

	vector<Trans> system;

	vector<string> transport_types;

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("data.xml");
	if (!result)return -1;

	pugi::xml_node dataset = doc.child("dataset");

	for (pugi::xml_node transport_station = dataset.first_child(); transport_station; transport_station = transport_station.next_sibling())
	{
		Trans station;
		station.num = transport_station.child_value("number");
		station.Type_of_vehicle = transport_station.child_value("type_of_vehicle");
		
		if (find(transport_types.begin(), transport_types.end(), station.Type_of_vehicle) == transport_types.end())
			transport_types.push_back(station.Type_of_vehicle);

		string str = transport_station.child_value("location");

		int i = 0;
		string token;
		while ((i = str.find(", ")) != std::string::npos) {
			token = str.substr(0, i);
			//cout << token << " ";
			station.Location.push_back(token);
			str.erase(0, i + 2);
		}station.Location.push_back(str);
		//cout << str << " ";


		str = transport_station.child_value("routes");
		for (int i = 0; i < str.length(); i++)
			if (str[i] == ',')
				str[i] = '.';


		i = 0;
		while ((i = str.find(".")) != std::string::npos) {
			token = str.substr(0, i);
			station.Routes.push_back(token);
			str.erase(0, i + 1);
		}
		station.Routes.push_back(str);


		str = transport_station.child_value("coordinates");

		i = 0;
		while ((i = str.find(",")) != std::string::npos) {
			token = str.substr(0, i);
			str.erase(0, i + 1);
		};
		token[2] = ','; str[2] = ',';
		station._X = stod(token); station._Y = stod(str);
		//cout << station._X << " "<< station._Y << endl;

		system.push_back(station);
	}


		/*most_station_route_num(system, transport_types[0]);
		cout << endl;*/

	cout << transport_types[0] << endl << transport_types[1] << endl << transport_types[2];
		most_station_route_num(system, transport_types[1]);
		cout << endl;
		/*
		most_station_route_num(system, transport_types[2]);
		cout << endl;*/
	/*for (int i = 0; i < transport_types.size(); i++) {
		cout << longest_route_num(system, transport_types[i]) << endl;
	}
	cout << most_stop_num(system) << endl;	*/

	cout << system.size() << endl;
}