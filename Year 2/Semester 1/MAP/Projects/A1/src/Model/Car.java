package Model;

public class Car implements Vehicle {
    private int repairCost;
    private String name;

    public Car(String name, int i){
        this.name = name;
        this.repairCost = i;
    }

    @Override
    public boolean checkRepairCost(int price) {
        return repairCost >= price;
    }

    @Override
    public void setRepairCost(int price){
        this.repairCost = price;
    }

    @Override
    public String getName() {
        return this.name;
    }

    @Override
    public int getRepairCost() {
        return this.repairCost;
    }

    @Override
    public String toString() {
        return "Car Name = " + this.name + " Repair cost = " + this.repairCost;
    }

}
