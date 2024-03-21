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

    // Рекурсивная функция для поиска путей
    void findPathsUtil(std::string current, std::string destination, int totalDistance, std::vector<std::string>& path) {
        if (current == destination) { // Если достигнут конечный город
            std::cout << "Путь: ";
            for (int i = 0; i < path.size() - 1; ++i) {
                std::cout << path[i] << " -> ";
            }
            std::cout << path[path.size() - 1] << std::endl;
            std::cout << "Общая длина: " << totalDistance << " км" << std::endl;
            std::cout << std::endl;
            return;
        }

        // Перебираем все дороги из текущего города
        for (const auto& road : cities[current].getRoads()) {
            if (std::find(path.begin(), path.end(), road.destination) == path.end()) { // Проверяем, что город не посещен
                std::vector<std::string> newPath = path;
                newPath.push_back(road.destination);
                findPathsUtil(road.destination, destination, totalDistance + road.distance, newPath); // Рекурсивный вызов для следующего города
            }
        }
    }

    // Вывод путей из одного города в другой с указанием общей протяженности
    void findPaths(std::string source, std::string destination) {
        if (cities.find(source) != cities.end() && cities.find(destination) != cities.end()) {
            std::vector<std::string> path = { source };
            findPathsUtil(source, destination, 0, path);
        }
        else {
            std::cout << "Один из указанных городов не найден в сети." << std::endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "Rus");
    CityNetwork network;

    network.addCity("Новосибирск");
    network.addCity("Омск");
    network.addCity("Красноярск");
    network.addCity("Томск");
    network.addCity("Караганда");


    network.addRoad("Новосибирск", "Омск", 300);
    network.addRoad("Новосибирск", "Красноярск", 600);
    network.addRoad("Красноярск", "Новосибирск", 600);
    network.addRoad("Омск", "Красноярск", 700);
    network.addRoad("Новосибирск", "Томск", 400);
    network.addRoad("Томск", "Красноярск", 500);
    network.addRoad("Омск", "Томск", 100);
    network.addRoad("Омск", "Караганда", 100);

    std::cout << "Пути из Новосибирска в Красноярск:" << std::endl;
    network.findPaths("Новосибирск", "Красноярск");

    network.removeRoad("Новосибирск", "Красноярск");
    network.removeCity("Томск");

    std::cout << "Пути из Новосибирска в Красноярск:" << std::endl;
    network.findPaths("Новосибирск", "Красноярск");

    return 0;
}
