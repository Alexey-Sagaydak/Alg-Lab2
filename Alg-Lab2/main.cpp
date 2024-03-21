#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

struct Road {
    std::string destination;
    int distance;
};

class City {
private:
    std::string name;
    std::vector<Road> roads;

public:
    City() {}

    City(std::string cityName) : name(cityName) {}

    void addRoad(std::string destination, int distance) {
        roads.push_back({ destination, distance });
    }

    std::string getName() const {
        return name;
    }

    std::vector<Road> getRoads() const {
        return roads;
    }

    void removeRoad(std::string destination) {
        for (auto it = roads.begin(); it != roads.end(); ++it) {
            if (it->destination == destination) {
                roads.erase(it);
                break;
            }
        }
    }
};

class CityNetwork {
private:
    std::unordered_map<std::string, City> cities;

public:
    void addCity(std::string cityName) {
        cities.insert({ cityName, City(cityName) });
    }

    void addRoad(std::string source, std::string destination, int distance) {
        cities[source].addRoad(destination, distance);
    }

    void removeCity(std::string cityName) {
        cities.erase(cityName);
    }

    void removeRoad(std::string source, std::string destination) {
        cities[source].removeRoad(destination);
    }

    // ����������� ������� ��� ������ �����
    void findPathsUtil(std::string current, std::string destination, int totalDistance, std::vector<std::string>& path) {
        if (current == destination) { // ���� ��������� �������� �����
            std::cout << "����: ";
            for (int i = 0; i < path.size() - 1; ++i) {
                std::cout << path[i] << " -> ";
            }
            std::cout << path[path.size() - 1] << std::endl;
            std::cout << "����� �����: " << totalDistance << " ��" << std::endl;
            std::cout << std::endl;
            return;
        }

        // ���������� ��� ������ �� �������� ������
        for (const auto& road : cities[current].getRoads()) {
            if (std::find(path.begin(), path.end(), road.destination) == path.end()) { // ���������, ��� ����� �� �������
                std::vector<std::string> newPath = path;
                newPath.push_back(road.destination);
                findPathsUtil(road.destination, destination, totalDistance + road.distance, newPath); // ����������� ����� ��� ���������� ������
            }
        }
    }

    // ����� ����� �� ������ ������ � ������ � ��������� ����� �������������
    void findPaths(std::string source, std::string destination) {
        if (cities.find(source) != cities.end() && cities.find(destination) != cities.end()) {
            std::vector<std::string> path = { source };
            findPathsUtil(source, destination, 0, path);
        }
        else {
            std::cout << "���� �� ��������� ������� �� ������ � ����." << std::endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "Rus");
    CityNetwork network;

    network.addCity("�����������");
    network.addCity("����");
    network.addCity("����������");
    network.addCity("�����");
    network.addCity("���������");


    network.addRoad("�����������", "����", 300);
    network.addRoad("�����������", "����������", 600);
    network.addRoad("����������", "�����������", 600);
    network.addRoad("����", "����������", 700);
    network.addRoad("�����������", "�����", 400);
    network.addRoad("�����", "����������", 500);
    network.addRoad("����", "�����", 100);
    network.addRoad("����", "���������", 100);

    std::cout << "���� �� ������������ � ����������:" << std::endl;
    network.findPaths("�����������", "����������");

    network.removeRoad("�����������", "����������");
    network.removeCity("�����");

    std::cout << "���� �� ������������ � ����������:" << std::endl;
    network.findPaths("�����������", "����������");

    return 0;
}
