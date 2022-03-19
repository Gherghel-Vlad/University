package Model;

public class Truck implements Vehicle {
    private int repairCost;
    private String name;
    public Truck(String name, int price){
        this.name = name;
        this.repairCost = price;
    }


    /**
     * Checks the repair cost if it s bigger than the given price
     * @param price The price to be compared to
     * @return True if the repair cost is bigger than the given price, false otherwise
     */
    @Override
    public boolean checkRepairCost(int price) {
        return this.repairCost >= price;
    }

    /**
     * Returns the repair cost
     * @return The repair cost
     */
    @Override
    public int getRepairCost() {
        return this.repairCost;
    }

    /**
     * Setter for repairCost field
     * @param price The price to set repairCost to (int)
     */
    @Override
    public void setRepairCost(int price) {
        this.repairCost = price;
    }

    @Override
    public String getName() {
        return this.name;
    }

    /**
     * Creates and returns a representation of the fields of the truck object
     * @return A string representation of the Truck object
     */
    @Override
    public String toString(){
        return "Truck Name = " + this.name + " Repair cost = " + this.repairCost;
    }

}
