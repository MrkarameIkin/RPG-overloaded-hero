#include <iostream>
#include <vector>

enum class HeroClass { Warrior, Mage, Rogue };

struct Item {
    std::string name;
    float weight;
    int value;
};

struct Hero {
    std::string name;
    HeroClass heroClass;
    int level;
    float maxWeight;
    std::vector<Item> inventory;
};

void createHero(Hero &player) {
    std::string input;

    std::cout << "=== СОЗДАНИЕ ГЕРОЯ ===\n";

    std::cout << "Имя: ";
    getline(std::cin, player.name);

    while(true) {
        std::cout << "Класс (1-Воин, 2-Маг, 3-Разбойник): ";

        getline(std::cin, input);

        if(input == "1") {
            player.heroClass = HeroClass::Warrior;
            break;
        }
        else if(input == "2") {
            player.heroClass = HeroClass::Mage;
            break;
        }
        else if(input == "3") {
            player.heroClass = HeroClass::Rogue;
            break;
        }
        else std::cout << "\nОшибка ввода!\n";
    }

    std::cout << "Уровень: ";

    getline(std::cin, input);
    player.level = stoi(input);

    std::cout << "Максимальный вес (кг): ";
    getline(std::cin, input);

    player.maxWeight = stof(input);
}

float inventoryWeight(const Hero &player)
{
    float weight = 0.0f;

    if(player.inventory.size() == 0) return 0.0f;

    for(int i = 0; i < player.inventory.size(); i++) weight += player.inventory[i].weight;

    return weight;
}

int inventoryValue(const Hero &player)
{
    int value = 0;

    if(player.inventory.size() == 0) return 0;

    for(int i = 0; i < player.inventory.size(); i++) value += player.inventory[i].value;

    return value;
}

void addItem(Hero &player) {
    Item newItem;
    std::string buffer;

    std::cout << "\nВы нашли предмет! Опишите его...\n";
    std::cout << "\nНазвание предмета: ";

    getline(std::cin, newItem.name);

    std::cout << "Вес предмета: ";

    getline(std::cin, buffer);
    newItem.weight = stof(buffer);

    std::cout << "Стоимость предмета: ";

    getline(std::cin, buffer);
    newItem.value = stoi(buffer);

    if(inventoryWeight(player) + newItem.weight > player.maxWeight) {
        std::cout << "\nОшибка: Герой не может унести это!\n";
        std::cout << "(итоговый вес станет " << inventoryWeight(player) + newItem.weight << " кг";
        std::cout << ", при максимальном весе " << player.maxWeight << " кг!)\n";
    }
    else {
        std::cout << "Предмет добавлен!\n";
        player.inventory.push_back(newItem);
    }
}

std::string heroClassOutput(const Hero &player) {
    if(player.heroClass == HeroClass::Warrior) return "Воин";
    else if(player.heroClass == HeroClass::Mage) return "Маг";
    else if(player.heroClass == HeroClass::Rogue) return "Разбойник";
}

void printHeroStats(const Hero &player) {
    std::cout << "\n--- СТАТУС ГЕРОЯ ---\n";
    std::cout << "Герой: " << player.name << " (" << heroClassOutput(player) << "), Уровень: " << player.level << '\n';
    std::cout << "Вес: " << inventoryWeight(player) << " / " << player.maxWeight << " кг\n";
    std::cout << "Общая ценность инвентаря: " << inventoryValue(player) << " золота\n";
    std::cout << "Инвентарь";

    if(player.inventory.size() == 0) {
        std::cout << " Пуст!";
        return;
    }
    else std::cout << ":\n";

    for(int i = 0; i < player.inventory.size(); i++) {
        std::cout << "- " << player.inventory[i].name << " (";
        std::cout << player.inventory[i].weight << " кг, ";
        std::cout << player.inventory[i].value << " з.)\n";
    }

    std::cout << "------------------\n";
}

void printMenu(Hero &player) {
    std::string input;

    while(true) {
        std::cout << "\n=== МЕНЮ ===\n";
        std::cout << "1. Найти предмет\n";
        std::cout << "2. Статус героя\n";
        std::cout << "3. Выход\n";
        std::cout << "\n> ";

        getline(std::cin, input);

        if(input == "1") addItem(player);
        else if(input == "2") printHeroStats(player);
        else if(input == "3") {
            std::cout << "\nДо свидания!\n\n";
            break;
        }
        else std::cout << "\nОшибка ввода!\n\n";
    }
}

int main() {
    Hero player;

    createHero(player);
    printMenu(player);

    return 0;
}