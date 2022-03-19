package Repository;
import Exceptions.RepoException;
import Model.Vehicle;

public interface IRepo {
    public void add(Vehicle v) throws RepoException;

    public void remove(String name) throws RepoException;

    public Vehicle[] filter(int price);

    public Vehicle[] getVehicles();

    public int getCurrentIndex();

    public void setCurrentIndex(int index) throws RepoException;

    public String toString();
}
