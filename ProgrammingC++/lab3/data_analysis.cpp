#include "data_analysis.h"

Solution_of_lab::Solution_of_lab(const char* name_of_file_)
{
    name_of_file = name_of_file_;
}

Point::Point(double x_, double y_){
    x = x_;
    y = y_;
}

Point::Point(){
    x = 0;
    y = 0;
}

double Point::getX() const{
    return x;
}

double Point::getY() const{
    return y;
}

//fixed list initialization
Station::Station(std::vector<std::string>& data)
{
    std::vector<std::string> arr_of_streets;
    std::string street;

    for (unsigned int i = 0; i < data[1].size(); i++)
    {
        if (data[1][i] == ',')
        {
            i++;
            arr_of_streets.push_back(street);
            street = "";
        }
        else
        {
            street += data[1][i];
        }
    }
    if (street != "")
    {
        arr_of_streets.push_back(street);
    }

    std::vector<std::string> arr_of_routes;
    std::string route;
    for (unsigned int i = 0; i < data[2].size(); i++)
    {
        if (data[2][i] == ',' || data[2][i] == '.')
        {
            arr_of_routes.push_back(route);
            route = "";
        }
        else
        {
            route += data[2][i];
        }
    }
    if (route != "")
    {
        arr_of_routes.push_back(route);
    }

    std::string coordinate;
    double x, y;
    for (unsigned int i = 0; i < data[3].size(); i++)
    {
        if (data[3][i] == ',')
        {
            x = std::stod(coordinate);
            coordinate = "";
        }
        else
        {
            coordinate += data[3][i];
        }
    }
    y = std::stod(coordinate);
    Point p = Point(x , y);

    type_of_vehicle = data[0];
    streets = arr_of_streets;
    routes = arr_of_routes;
    coordinates = p;
}

int Station::getSizeStr() const
{
    return streets.size();
}

int Station::getSizeRte() const
{
    return routes.size();
}

std::string Station::getStreet(int number) const
{
    return streets[number];
}

std::string Station::getRoute(int number) const
{
    return routes[number];
}

std::string Station::getVehicle() const
{
    return type_of_vehicle;
}

Point Station::getCoord() const
{
    return coordinates;
}

double Station::distBetweenSt(const Station& other) const
{
    return sqrt(pow(coordinates.getX() - other.getCoord().getX(), 2) + pow(coordinates.getY() - other.getCoord().getY(), 2));
}

std::vector<Station> Solution_of_lab::parseToStations() const
{
    pugi::xml_document doc;
    doc.load_file(name_of_file);
    pugi::xml_node dataset = doc.first_child();
    std::vector<Station> stations;
    for (pugi::xml_node transport_station = dataset.first_child(); transport_station; transport_station = transport_station.next_sibling())
    {
		auto node = transport_station.first_child().next_sibling();
        std::string type_of_vehicle = node.first_child().value();

		node = node.next_sibling().next_sibling().next_sibling().next_sibling();
		std::string streets = node.first_child().value();


		node = node.next_sibling();
        std::string routes = node.first_child().value();

		node = node.next_sibling();
        std::string coordinates = node.first_child().value();

        std::vector<std::string> data{type_of_vehicle, streets, routes, coordinates};

        Station st(data);
        stations.push_back(st);
    }
    return stations;
}

std::vector<std::map<std::string, std::vector<Station>>> Solution_of_lab::parseToRoutes(std::vector<Station>& stations) const
{
    std::vector<std::map<std::string, std::vector<Station>>> parsed;
    std::map<std::string, std::vector<Station>> map_of_routes_bus, map_of_routes_trolleybus, map_of_routes_tram;
    for (Station st : stations)
    {
        for (int i = 0; i < st.getSizeRte(); i++)
        {
            std::string rte = st.getRoute(i);
            if (rte != "")
            {
                if (st.getVehicle().length() == 2*7)
                {
                    // bus
                    if (st.getVehicle()[0] == st.getVehicle()[2])
                    {
                        map_of_routes_bus[rte].emplace_back(st);
                    }
                    // tram
                    else
                    {
                        map_of_routes_tram[rte].emplace_back(st);
                    }
                }
                // trolleybus
                else
                {
                    map_of_routes_trolleybus[rte].emplace_back(st);
                }
            }
        }
    }

    parsed.push_back(map_of_routes_bus);
    parsed.push_back(map_of_routes_tram);
    parsed.push_back(map_of_routes_trolleybus);
    return parsed;
}

void Solution_of_lab::task1_solution(std::vector<std::map<std::string, std::vector<Station>>>& parsed) const
{
    for (int i = 0; i < 3; i++)
    {
        std::string longest_route;
        unsigned int size_longest_route = 0;
        for (auto& [name, vect]: parsed[i])
        {
            if (vect.size() >= size_longest_route)
            {
                longest_route = name;
                size_longest_route = vect.size();
            }
        }
        switch (i)
        {
        case 0:
            std::cout << "The longest route for bus is: " << longest_route << " with " << size_longest_route << " stations!\n";
            break;
        case 1:
            std::cout << "The longest route for tram is: " << longest_route << " with " << size_longest_route << " stations!\n";
            break;
        case 2:
            std::cout << "The longest route for trolleybus is: " << longest_route << " with " << size_longest_route << " stations!\n";
            break;
        }
    }
}

void Solution_of_lab::task2_solution(std::vector<std::map<std::string, std::vector<Station>>>& parsed) const
{
    //fixed copy-paste
    for (int i = 0; i < 3; i++)
    {
        std::string longest_route;
        double len_longest_route = 0;
        for (auto& [name, vect]: parsed[i])
        {
            if (lenOfRoute(vect) >= len_longest_route)
            {
                longest_route = name;
                len_longest_route = lenOfRoute(vect);
            }
        }
        //fixed random const
        len_longest_route *= DEG_to_KM;
        switch (i)
        {
        case 0:
            std::cout << "The longest route for bus is: " << longest_route << " with " << len_longest_route << " kilometers!\n";
            break;
        case 1:
            std::cout << "The longest route for tram is: " << longest_route << " with " << len_longest_route << " kilometers!\n";
            break;
        case 2:
            std::cout << "The longest route for trolleybus is: " << longest_route << " with " << len_longest_route << " kilometers!\n";
            break;
        }
    }
}

void Solution_of_lab::task3_solution(std::vector<Station>& stations) const
{
    std::map<std::string, std::vector<Station>> map_of_street;
    std::string longest_street;
    unsigned int size_of_longest_street = 0;
    for (Station st : stations)
    {
        for (int i = 0; i < st.getSizeStr(); i++)
        {
            std::string str = st.getStreet(i);
            map_of_street[str].push_back(st);
            if  (map_of_street[str].size() >= size_of_longest_street)
            {
                size_of_longest_street = map_of_street[str].size();
                longest_street = str;
            }
        }
    }
    std::cout << "The longest street is: " << longest_street << " with " << size_of_longest_street << " stations!\n";
}

//fixed const&
double lenOfRoute(const std::vector<Station>& route)
{
    std::vector<bool> used(route.size(), false);
    used[0] = true;
    int startSt = 0, endSt = 0;
    double len_of_route = 0;
    for (unsigned int i = 0; i < route.size() - 1; i++)
    {
        int closestToStart, closestToEnd;
        double min_distToStart = DBL_MAX, min_distToEnd = DBL_MAX;
        for (unsigned int j = 0; j < route.size(); j++)
        {
            if (i != j && !used[j])
            {
                if (route[j].distBetweenSt(route[startSt]) < min_distToStart)
                {
                    closestToStart = j;
                    min_distToStart = route[j].distBetweenSt(route[startSt]);
                }
                if (route[j].distBetweenSt(route[endSt]) < min_distToEnd)
                {
                    closestToEnd = j;
                    min_distToEnd = route[j].distBetweenSt(route[endSt]);
                }
            }
        }
        if (min_distToStart <= min_distToEnd)
        {
            used[closestToStart] = true;
            startSt = closestToStart;
            len_of_route += min_distToStart;
        }
        else
        {
            used[closestToEnd] = true;
            endSt = closestToEnd;
            len_of_route += min_distToEnd;
        }
    }
    if (len_of_route != DBL_MAX)
    {
        return len_of_route;
    }
    return 0;
}
