#include "main.h"

int main() {
    Warehouse warehouse;

    auto product1 = std::make_shared<PerishableProduct>(
            "Milk", 101, 1.0, 2.5, 5, time(nullptr) + 5 * 86400
    );

    auto product2 = std::make_shared<ElectronicProduct>(
            "Laptop", 201, 2.5, 1200.0, 30, 365, 60.0
    );

    auto product3 = std::make_shared<BuildingMaterial>(
            "Paint", 301, 5.0, 50.0, 0, 2
    );

    warehouse += product1;
    warehouse += product2;
    warehouse += product3;

    auto bread = std::make_shared<PerishableProduct>(
            "Bread", 102, 0.5, 1.5, 3, time(nullptr) + 3 * 86400
    );
    warehouse += bread;

    auto oldBread = std::make_shared<PerishableProduct>(
            "Old Bread", 103, 0.4, 1.0, -2, time(nullptr) - 2 * 86400
    );
    warehouse += oldBread;

    // Create and add additional ElectronicProducts
    auto ledBulb = std::make_shared<ElectronicProduct>(
            "LED Bulb", 202, 0.1, 5.0, 1000, 730, 10.0
    );
    warehouse += ledBulb;

    auto usbCable = std::make_shared<ElectronicProduct>(
            "USB Cable", 203, 0.05, 2.0, 365, 0, 0.5
    );
    warehouse += usbCable;

    // Create and add additional BuildingMaterials
    auto woodPlank = std::make_shared<BuildingMaterial>(
            "Wood Plank", 302, 10.0, 30.0, 0, 1
    );
    warehouse += woodPlank;

    auto gasCanister = std::make_shared<BuildingMaterial>(
            "Gas Canister", 303, 2.0, 50.0, 0, 5
    );
    warehouse += gasCanister;

    // Display warehouse inventory
    std::cout << "Initial Inventory:\n";
    std::cout << warehouse;

    // Test getting expiring products within 4 days
    std::cout << "Expiring products within 4 days:\n";
    auto expiringIn5Days = warehouse.getExpiringProducts(4);
    for (const auto& p : expiringIn5Days) {
        p->displayInfo();
        std::cout << '\n';
    }

    // Test deleting a product by ID
    std::cout << "Deleting product with ID 101 (Milk)\n";
    warehouse -= 101;
    std::cout << warehouse;

    // Test accessing a product by ID
    std::cout << "Accessing product with ID 202 (LED Bulb)\n";
    auto product = warehouse[202];
    if (product) {
        product->displayInfo();
    } else {
        std::cout << "Product not found.\n";
    }

    // Test accessing a non-existent product by ID
    std::cout << "Accessing product with ID 999 (Non-existent)\n";
    auto nonExistent = warehouse[999];
    if (nonExistent) {
        nonExistent->displayInfo();
    } else {
        std::cout << "Product not found.\n";
    }

    return 0;
}