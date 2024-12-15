#ifndef FUNDAMENTAL_ALGORITHMS_MAIN_H
#define FUNDAMENTAL_ALGORITHMS_MAIN_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <memory>
#include <algorithm>

class Product {
public:
    std::string label;
    int ID;
    float weight;
    double price;
    int expiration_days;

    Product(const std::string& label, int ID, float weight, double price, int expiration_days)
            : label(label), ID(ID), weight(weight), price(price), expiration_days(expiration_days) {}

    Product(const Product &val) = default;

    Product& operator=(const Product &val);

    virtual ~Product() = default;

    virtual double calculateStorageFee() const {
        return price;
    }

    virtual void displayInfo() const;

    virtual std::string getCategory() const {
        return "Product";
    }
};

class PerishableProduct : public Product {
public:
    time_t expirationDate;

    PerishableProduct(const std::string& label, int ID, float weight, double price, int expiration_days, time_t expirationDate)
            : Product(label, ID, weight, price, expiration_days), expirationDate(expirationDate) {}

    PerishableProduct(const PerishableProduct& pp) = default;

    PerishableProduct& operator=(const PerishableProduct& pp) = default;

    ~PerishableProduct() override = default;

    double calculateStorageFee() const override;

    void displayInfo() const override;

    std::string getCategory() const override;
};

class ElectronicProduct : public Product {
public:
    int warrantyPeriod;
    float powerRating;

    ElectronicProduct(const std::string& label, int ID, float weight, double price, int expiration_days, int warrantyPeriod, float powerRating)
            : Product(label, ID, weight, price, expiration_days), warrantyPeriod(warrantyPeriod), powerRating(powerRating) {}

    ElectronicProduct(const ElectronicProduct& ep) = default;

    ElectronicProduct& operator=(const ElectronicProduct& ep) = default;

    ~ElectronicProduct() override = default;

    void displayInfo() const override;

    std::string getCategory() const override;
};

class BuildingMaterial : public Product {
public:
    int flammability;

    BuildingMaterial(const std::string& label, int ID, float weight, double price, int expiration_days, int flammability)
            : Product(label, ID, weight, price, expiration_days), flammability(flammability) {}

    BuildingMaterial(const BuildingMaterial& bm) = default;

    BuildingMaterial& operator=(const BuildingMaterial& bm) = default;

    ~BuildingMaterial() override = default;

    double calculateStorageFee() const override;

    void displayInfo() const override;

    std::string getCategory() const override;
};

class Warehouse {
public:
    using product_ptr = std::shared_ptr<Product>;
    using product_ptr_vector = std::vector<product_ptr>;

    product_ptr_vector productList;

    void add_product(const product_ptr& product);

    product_ptr find_product_by_id(int product_id) const;

    bool delete_product(int product_id);

    product_ptr_vector find_products_by_category(const std::string& category) const;

    double calculate_storage_price() const;

    product_ptr_vector getExpiringProducts(int days) const;

    void displayInventory() const;

    Warehouse& operator+=(const product_ptr& product);

    Warehouse& operator-=(int product_id);

    product_ptr operator[](int product_id) const;

    friend std::ostream& operator<<(std::ostream& stream, const Warehouse& warehouse);
};

#endif // FUNDAMENTAL_ALGORITHMS_MAIN_H