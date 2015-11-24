
import java.util.concurrent.locks.*;

public class SharedSavingsAccount {
  
  long balance;
  Lock lock = new ReentrantLock();
  Condition cond = lock.newCondition();

  public SharedSavingsAccount(long initialBalance){
    balance = initialBalance;
  }
  
  public void deposit(int amount){
    try{
      lock.lock();
      balance += amount;
      cond.signalAll();
    } finally{
      lock.unlock();
    }
  }
  
  public void withdraw(int amount) throws InterruptedException{
    try{
      lock.lock();
      long computation = balance-amount;
      while(!(computation >= 0)){ cond.await();}
      balance = computation;
    } finally{
      lock.unlock();
    }
  }
  
}
