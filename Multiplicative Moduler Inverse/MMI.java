import java.math.*;
import java.util.*;

class MMI
{
  static BigInteger modInverse(BigInteger a, BigInteger m)
    {
        BigInteger m0 = m;
        BigInteger y , x ,one,zero;
        y=new BigInteger("0");
        x=new BigInteger("1");
        one=x;
        zero=y;
        if (m.compareTo(one)==0)
            return zero;
 
        while (a.compareTo(one)==1)
        {
           
            BigInteger q = a.divide(m);
 
            BigInteger t = m;
 
           
            m = a.mod(m);
            a = t;
            t = y;
 
           y= x.subtract(q.multiply(y));
		   x=t;
        }
 
     
        if (x.compareTo(zero)==-1)
            x = x.add(m0);
 
        return x;
    }
 
    
    public static void main(String args[])
    {
        
		BigInteger bi1, bi2,one;
		
		Scanner sc = new Scanner(System.in);
 	         System.out.println("Enter A and M");
                 bi1 = sc.nextBigInteger();
		 bi2 = sc.nextBigInteger();
		 one=new BigInteger("0");
		 
		/* if((bi2.mod(bi1)).compareTo(one)==0)
		  {
		   System.out.println("Modular multiplicative Doesn't exist");
		   return ;
		  }
		*/
		System.out.println("Modular multiplicative "+
                           "inverse is " + modInverse(bi1, bi2));
    }
}
 

