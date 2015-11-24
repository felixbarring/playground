
import java.util.concurrent.locks.*;
import java.util.List;
import java.util.LinkedList;

public class Pootify {
  
  List<String> songs = new LinkedList<String>();
  
  ReentrantLock lock = new ReentrantLock();
  Condition readers = lock.newCondition();
  Condition writers = lock.newCondition();
  boolean writing = false;
  int numberOfReaders = 0;

  public void songInfo(String name) throws InterruptedException{
    try{
      lock.lock();
      while(writing) readers.await(); 
      numberOfReaders++;
      lock.unlock();
      songs.get(songs.indexOf(name)); // return
      lock.lock();
      if (--numberOfReaders == 0) writers.signal();
      lock.unlock();
    } finally {
      lock.unlock();
    }
  }
  
  public void addSong(String name) throws InterruptedException{
    try{
      lock.lock();
      while(numberOfReaders > 0 || writing) writers.await();
      writing = true;
      lock.unlock();
      songs.add(name);
      lock.lock();
      writing = false;
      lock.unlock();
      writers.signal();
      readers.signalAll();
    }finally{
      lock.unlock();
    }
  }
  
}
