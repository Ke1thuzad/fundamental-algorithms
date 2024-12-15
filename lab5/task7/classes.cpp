#include "main.h"

Product &Product::operator=(const Product &val) {
    if (this != &val) {
        label = val.label;
        ID = val.ID;
        weight = val.weight;
        price = val.price;
        expiration_days = val.expiration_days;
    }
    return *this;
}

void Product::displayInfo() const {
    std::cout << "Label: " << label << "\nID: " << ID << "\nWeight: " << weight
              << "\nPrice: " << price << "$\nExpiration Days: " << expiration_days << "\n";
}

double PerishableProduct::calculateStorageFee() const {
    double daysUntilExpiration = difftime(expirationDate, time(nullptr)) / 86400.0;
    if (daysUntilExpiration < 0) daysUntilExpiration = 0;
    return price * (1 + 0.05 * daysUntilExpiration);
}

void PerishableProduct::displayInfo() const {
    Product::displayInfo();
    std::cout << "Expiration Date: " << ctime(&expirationDate);
}

std::string PerishableProduct::getCategory() const {
    return "PerishableProduct";
}

void ElectronicProduct::displayInfo() const {
    Product::displayInfo();
    std::cout << "Warranty Period: "  << warrantyPeriod << " days\n"
              << "Power Rating: " << powerRating << " W\n";
}

std::string ElectronicProduct::getCategory() const {
    return "ElectronicProduct";
}

double BuildingMaterial::calculateStorageFee() const {
    return price * (1 + 0.5 * flammability);
}

void BuildingMaterial::displayInfo() const {
    Product::displayInfo();
    std::cout << "Flammability Level: " << flammability << "\n";
}

std::string BuildingMaterial::getCategory() const {
    return "BuildingMaterial";
}

void Warehouse::add_product(const product_ptr& product) {
    productList.push_back(product);
}

Warehouse::product_ptr Warehouse::find_product_by_id(int product_id) const {
    for (const auto& product : productList) {
        if (product->ID == product_id) {
            return product;
        }
    }
    return nullptr;
}

bool Warehouse::delete_product(int product_id) {
    auto it = std::remove_if(productList.begin(), productList.end(),
                             [product_id](const product_ptr& p) { return p->ID == product_id; });
    if (it != productList.end()) {
        productList.erase(it);
        return true;
    }
    return false;
}

Warehouse::product_ptr_vector Warehouse::find_products_by_category(const std::string &category) const {
    product_ptr_vector result;
    for (const auto& product : productList) {
        if (product->getCategory() == category) {
            result.push_back(product);
        }
    }
    return result;
}

double Warehouse::calculate_storage_price() const {
    double total = 0.0;
    for (const auto& product : productList) {
        total += product->calculateStorageFee();
    }
    return total;
}

Warehouse::product_ptr_vector Warehouse::getExpiringProducts(int days) const {
    time_t now = time(nullptr);
    product_ptr_vector expiring;
    for (const auto& product : productList) {
        if (product->getCategory() == "PerishableProduct") {
            auto perishable = std::dynamic_pointer_cast<PerishableProduct>(product);
            if (perishable) {
                double daysUntilExpiration = difftime(perishable->expirationDate, now) / 86400.0;
                if (daysUntilExpiration <= days) {
                    expiring.push_back(perishable);
                }
            }
        }
    }
    return expiring;
}

void Warehouse::displayInventory() const {
    std::string categories[] = {"PerishableProduct", "ElectronicProduct", "BuildingMaterial"};
    for (const auto& category : categories) {
        std::cout << "List of all " << category << " types:\n\n";
        product_ptr_vector products = find_products_by_category(category);
        for (const auto& product : products) {
            product->displayInfo();
            std::cout << "\n";
        }
        std::cout << "\n\n";
    }
}

Warehouse &Warehouse::operator+=(const product_ptr& product) {
    add_product(product);
    return *this;
}

Warehouse &Warehouse::operator-=(int product_id) {
    delete_product(product_id);
    return *this;
}

Warehouse::product_ptr Warehouse::operator[](int product_id) const {
    return find_product_by_id(product_id);
}

std::ostream &operator<<(std::ostream &stream, const Warehouse &warehouse) {
    stream << "Total Products: " << warehouse.productList.size() << "\n"
           << "Total Storage Cost: " << warehouse.calculate_storage_price() << "$\n\n";
    warehouse.displayInventory();
    return stream;
}
