package Repository;
import Exceptions.RepoException;
import Model.Vehicle;

import java.util.Objects;

public class Repo implements IRepo
{
    private Vehicle[] list;
    private int currentIndex, size;

    public Repo(){
        super();
        this.list = new Vehicle[100];
        this.size = 100;
        this.currentIndex = 0;
    }

    @Override
    public void add(Vehicle v) throws RepoException {
        if(this.currentIndex >= this.size)
            throw new RepoException("Array is full. Max size is: " + this.size);

        if(v.getRepairCost() < 0)
            throw new RepoException("The price cant be negative!" + v.toString());
        for(int i = 0; i <this.currentIndex;i++){
            if(Objects.equals(this.list[i].getName(), v.getName())){
                throw new RepoException("There already is a vehicle with the given name " + v.getName());
            }
        }


        this.list[this.currentIndex++] = v;

    }

    @Override
    public void remove(String name) throws RepoException {
        boolean found = false;

//        for(int i = 0; i <this.currentIndex;i++){
//            if(this.list[i].getRepairCost() == v.getRepairCost() && list[i].getClass() == v.getClass()){
//                found = true;
//                if(i==currentIndex -1){
//                    list[i]=null;
//                }
//                else{
//                    this.list[i] = list[currentIndex-1];
//                }
//                currentIndex--;
//
//            }
//        }

        for(int i = 0; i <this.currentIndex;i++){
            if(Objects.equals(this.list[i].getName(), name)){
                found=true;
                if(i==currentIndex -1){
                    list[i]=null;
                }
                else{
                    this.list[i] = list[currentIndex-1];
                }
                currentIndex--;
            }

        }

        if(!found){
            throw new RepoException("Specified vehicle was not found.");
        }
    }

    @Override
    public Vehicle[] filter(int price) {
        Vehicle[]  result = new Vehicle[currentIndex];
        int resultIndex = 0;

        for(int i = 0;i< currentIndex;i++){
            if(list[i].checkRepairCost(price)){
                result[resultIndex++] = list[i];
            }
        }

        return result;
    }

    @Override
    public Vehicle[] getVehicles() {
        return list;
    }

    @Override
    public int getCurrentIndex() {
        return currentIndex;
    }

    @Override
    public void setCurrentIndex(int index) throws RepoException{
        if(index < 0 || index > this.currentIndex){
            throw new RepoException("The index given is not correct. It must be between 0 and " + this.currentIndex);
        }

        currentIndex = index;
    }

    @Override
    public String toString(){
        StringBuilder result = new StringBuilder();

        for(int i = 0;i< currentIndex;i++){
            result.append(this.list[i].toString()).append("\n");
        }
        return result.toString();
    }

}
