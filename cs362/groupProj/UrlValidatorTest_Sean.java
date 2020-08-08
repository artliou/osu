
import junit.framework.TestCase;
import java.security.*;
import java.util.Random;


public class UrlValidatorTest extends TestCase {
	
		//The following test cases are derived from UrlValidatorTest.java, Result Pairs
	   String[] trueScheme = {
			   "http://",
			   "ftp://",
			   "h3t://"
	   };

	   String[] falseScheme = {
			   "3ht://",
			   "http:/",
			   "http:",
			   "http/",
			   "://"
	   };

	   String[] trueAuthority = {
			   "www.google.com",
			   "go.com",
			   "go.au",
			   "0.0.0.0",
			   "255.255.255.255",
			   "255.com",
			   "go.cc"
	   };

	   String[] falseAuthority = {
			   "256.256.256.256",
			   "1.2.3.4.5",
			   "1.2.3.4.",
			   "1.2.3",
			   ".1.2.3.4",
			   "go.a",
			   "go.a1a",
			   "go.1aa",
			   "aaa.",
			   ".aaa",
			   "aaa",
			   ""
	   };

	   String[] truePort = {
			   ":80",
			   ":65535",
			   ":0",
			   ""
	   };

	   String[] falsePort = {
			   ":-1",
			   ":65a",
			   ":65636",
			   ":999999999999999999"
	   };

	   String[] truePath = {
			   "/test1",
			   "/t123",
			   "/$23",
			   "/test1/",
			   "",
			   "/test1/file"
	   };

	   String[] falsePath = {
			   "/..",
			   "/../",
			   "/..//file",
			   "/test1//file"
	   };

	public UrlValidatorTest(String testName) {
		super(testName);
	}
	
	public void testIsValidForTrue()
	{
		System.out.println("Random Test");
		
		//Randomness Generator
		//Ref: https://stackoverflow.com/questions/5887709/getting-random-numbers-in-java
		Random random = new Random();
		
		String generatedURL = "";
		UrlValidator checker;
		
		//Loop for randomizing
		for(int i = 0; i < 10; i++)
		{
			//Randomized Number
			int urlScheme = random.nextInt(3);
			int urlAuthority = random.nextInt(7);
			int urlPort = random.nextInt(4);
			int urlPath = random.nextInt(6);
			
			//Combined new URL
			generatedURL = trueScheme[urlScheme] + 
					       trueAuthority[urlAuthority] +
					       truePort[urlPort] + 
					       truePath[urlPath];

			checker = new UrlValidator(null, null, UrlValidator.ALLOW_LOCAL_URLS);
			
			System.out.println("----------True URL Test----------");
			
			boolean passed = checker.isValid(generatedURL);
			if(passed)
			{
				System.out.println("Test PASSED!");
			}
			else
			{
				System.out.println("Test FAILED!");
				System.out.println("URL: " + generatedURL);
			}
		}
		System.out.println("Random Testing For True Test Ending");
	}
	
	public void testIsValidForFalse()
	{		
		//Randomness Generator
		//Ref: https://stackoverflow.com/questions/5887709/getting-random-numbers-in-java
		Random random = new Random();
	
		String generatedURL = "";
		UrlValidator checker;
		
		//Loop for randomizing
		for(int i = 0; i < 10; i++)
		{
			//Choose a random from provided list
			int urlScheme = random.nextInt(3);
			int urlAuthority = random.nextInt(12);
			int urlPort = random.nextInt(4);
			int urlPath = random.nextInt(4);
		
		generatedURL = falseScheme[urlScheme] + 
					   falseAuthority[urlAuthority] +
					   falsePort[urlPort] +
					   falsePath[urlPath];
		
		checker = new UrlValidator(null, null, UrlValidator.ALLOW_LOCAL_URLS);
		
		 System.out.println("----------FALSE URL TEST----------");
		 boolean passed = checker.isValid(generatedURL);
		 
		 if (!passed)
		 {
			 System.out.println("TEST PASS!");
		 }
		 else
		 {
			 System.out.println("TEST FAIL!");
			 System.out.println("URL Fail: " + generatedURL);
		  }
	   }
	   System.out.println("Random Testing for False Test End");
	}
}