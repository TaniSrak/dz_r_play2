#include <iostream>
#include <vector>

using namespace std;


class Item
{
public:

	string GetName()
	{
		return name_;
	}

	Item(string name) : name_ {name}
	{
		name_ = name;
	}
protected:
	string name_;
};

class Hat : public Item
{
public:

	Hat(string name) : Item(name) {}
};

class Potion : public Item //зелье
{
public:
	int Use()
	{
		return impact_;
	}
	Potion(int impact, string name) : Item(name)
	{
		impact_ = impact;
	}
private:
	int impact_;
};
class Inventory
{
public:
	Inventory() 
	{ 
		items = vector<Item*>(0); 
	}
	void AddItem(Item* i)
	{
		items.push_back(i); 
	}
	Item* FindIetemByName(string name)
	{
		auto iter = items.cbegin();
		for (int i = 0; i < items.size(); i++)
		{
			if (items[i]->GetName() == name)
			{
				Item* targetItem = items[i];
				items.erase(iter + i); //метод удаляющий элемент по месту, на кот указывает итератор

				return targetItem;
			}
		}
		return nullptr;
	}

private:
	vector<Item*> items;
};

class Character
{
public:
	Inventory* GetCharacterInventory()
	{
		return characterInventory_;
	}

	void HealCharacter(int healImpact)
	{
		health_ += healImpact;
	}

	Character(string name, int age, Inventory* backpack)
	{
		characterInventory_ = backpack;
		name_ = name;
		age_ = age;
		health_ = 100;
		attachedHat_ = nullptr;
	}

private:
	string name_;
	int age_;
	int health_;
	Inventory* characterInventory_;
	Hat* attachedHat_;
};

int main() {
	setlocale(LC_ALL, "Russian");
	int n;

	Potion testPotion = Potion(10, "Poter");
	Item t = Item{ testPotion };

	Inventory backpack = Inventory();
	backpack.AddItem(&t);

	Character ch = Character("Poter", 25, &backpack);

	Item* itemFromBackPack = ch.GetCharacterInventory()->FindIetemByName("Poter");
	if (itemFromBackPack != nullptr)
	{
		std::cout << "Зелье найдено\n";
		Potion* healPotion = (Potion*)itemFromBackPack;
		ch.HealCharacter(healPotion->Use());
	}
	else
	{
		std::cout << "Зелье не найдено\n";
	}

	//сделать еще чтобы можно бфло надевать

	

	std::cout << t.GetName();


	return 0;
}