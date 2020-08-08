
import junit.framework.TestCase;
import java.security.*;
import java.util.Random;

public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }


    public void testManualTest()
   {
//You can use this function to implement your manual testing      
      System.out.print("************** Start Manual Test **************\n");
      
      UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
      
      // Testing when url is NULL.
      System.out.print("\nTesting NULL url:(NULL)\nExpected result: false. Actual Result: ");
      System.out.println(urlVal.isValid(""));
      
      // Testing when url structure is invalid.
      System.out.print("\nTesting url structure: http::/manualTest_1.com/-lol\nExpected result: false. Actual Result: ");
      System.out.println(urlVal.isValid("http::/manualTest_1.com/lol"));
      
      // Testing valid urls. Each url component is tested with one valid and one invalid of each element. 
      System.out.print("\nTesting valid url: http://manualTest_1.com:1080/lol\nExpected result: true. Actual Result: ");
      System.out.println(urlVal.isValid("http://manualTest_1.com/lol"));
      
      // Testing scheme.
      System.out.print("\nTesting url scheme: 3ht://manualTest_1.com/lol\nExpected result: false. Actual Result: ");
      System.out.println(urlVal.isValid("3ht://manualTest_1.com/lol"));
      
      // Testing scheme.
//    System.out.print("\nTesting url scheme: https://manualTest_1.com:1080/lol\nExpected result: false. Actual Result: ");
//    System.out.println(urlVal.isValid("https://manualTest_1.com:1080/lol"));
      
      // Testing scheme.
//    System.out.print("\nTesting url scheme: ftp://manualTest_1.com:1080/lol\nExpected result: false. Actual Result: ");
//    System.out.println(urlVal.isValid("ftp://manualTest_1.com:1080/lol"));
      
      // Testing authority.
      System.out.print("\nTesting url authority: http://aaa/lol\nExpected result: false. Actual Result: ");
      System.out.println(urlVal.isValid("3ht://aaa/lol"));
      
      // Testing path.
      System.out.print("\nTesting url path: http://manualTest_1.com//lol\nExpected result: false. Actual Result: ");
      System.out.println(urlVal.isValid("http://manualTest_1.com//lol"));
      
      // Testing query.
      System.out.print("\nTesting url query: http://manualTest_1.com/lol/#page=123\nExpected result: false. Actual Result: ");
      System.out.println(urlVal.isValid("http://manualTest_1.com/lol/#page=123"));  
      
      System.out.print("\n");
      System.out.print("************** End Manual Test **************\n");
   }

   

   /***
    * Unit/Programming Testing
    */
   public void testEdgeCase() {
      System.out.println("----------Unit Test Edge Cases----------");

      UrlValidator urlValidator = new UrlValidator();

      System.out.println("Unit Test - Edge Case: Empty String");
      if (urlValidator.isValid("")) {
         System.out.println("Failed! Found an empty URL to be Valid");
      } else {
         System.out.println("Passed! Found an empty URL to be inValid");
      }

      System.out.println("Unit Test - Edge Case: Zip Code as URL");
      if (urlValidator.isValid("97331")) {
         System.out.println("Failed! Found a Purely Numeric URL to be Valid");
      } else {
         System.out.println("Passed! Found a Purely Numeric URL to be inValid");
      }

      System.out.println("Unit Test - Edge Case: Null");
      if (urlValidator.isValid(null)) {
         System.out.println("Failed! Found a null URL to be Valid");
      } else {
         System.out.println("Passed! Found a null URL to be inValid");
      }

      System.out.println("----------Unit Test Edge Cases - Complete----------");
   }

   // Construct a UrlValidator with valid schemes of "http", and "https".
   public void testBasicValidator() {
      System.out.println("----------Starting basicTestValidator----------");
      String[] schemes = { "http", "https" };
      UrlValidator urlValidator = new UrlValidator(schemes);
      if (urlValidator.isValid("ftp://foo.bar.com/")) {
         System.out.println("url found valid with schemes");
         System.out.println("Unit Test Failed! Invalid URL: 'ftp://foo.bar.com/'");
      } else {
         System.out.println("url found invalid with schemes");
         System.out.println("Unit Test Passed! URL: 'ftp://foo.bar.com/'");
      }
      // prints "url is invalid"
      System.out.println("----------testBasicValidator - Complete----------");
   }

   /***
    * Random Testing The following test cases are derived from
    * UrlValidatorTest.java, Result Pairs
    */
   String[] trueScheme = { "http://", "ftp://", "h3t://" };

   String[] falseScheme = { "3ht://", "http:/", "http:", "http/", "://" };

   String[] trueAuthority = { "www.google.com", "go.com", "go.au", "0.0.0.0", "255.255.255.255", "255.com", "go.cc" };

   String[] falseAuthority = { "256.256.256.256", "1.2.3.4.5", "1.2.3.4.", "1.2.3", ".1.2.3.4", "go.a", "go.a1a",
         "go.1aa", "aaa.", ".aaa", "aaa", "" };

   String[] truePort = { ":80", ":65535", ":0", "" };

   String[] falsePort = { ":-1", ":65a", ":65636", ":999999999999999999" };

   String[] truePath = { "/test1", "/t123", "/$23", "/test1/", "", "/test1/file" };

   String[] falsePath = { "/..", "/../", "/..//file", "/test1//file" };

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   public void testIsValidForTrue() {
      System.out.println("Random Test");

      // Randomness Generator
      // Ref:
      // https://stackoverflow.com/questions/5887709/getting-random-numbers-in-java
      Random random = new Random();

      String generatedURL = "";
      UrlValidator checker;

      // Loop for randomizing
      for (int i = 0; i < 10; i++) {
         // Randomized Number
         int urlScheme = random.nextInt(3);
         int urlAuthority = random.nextInt(7);
         int urlPort = random.nextInt(4);
         int urlPath = random.nextInt(6);

         // Combined new URL
         generatedURL = trueScheme[urlScheme] + trueAuthority[urlAuthority] + truePort[urlPort] + truePath[urlPath];

         checker = new UrlValidator(null, null, UrlValidator.ALLOW_LOCAL_URLS);

         System.out.println("----------True URL Test----------");

         boolean passed = checker.isValid(generatedURL);
         if (passed) {
            System.out.println("Test PASSED!");
         } else {
            System.out.println("Test FAILED!");
            System.out.println("URL: " + generatedURL);
         }
      }
      System.out.println("Random Testing For True Test Ending");
   }

   public void testIsValidForFalse() {
      // Randomness Generator
      // Ref:
      // https://stackoverflow.com/questions/5887709/getting-random-numbers-in-java
      Random random = new Random();

      String generatedURL = "";
      UrlValidator checker;

      // Loop for randomizing
      for (int i = 0; i < 10; i++) {
         // Choose a random from provided list
         int urlScheme = random.nextInt(3);
         int urlAuthority = random.nextInt(12);
         int urlPort = random.nextInt(4);
         int urlPath = random.nextInt(4);

         generatedURL = falseScheme[urlScheme] + falseAuthority[urlAuthority] + falsePort[urlPort] + falsePath[urlPath];

         checker = new UrlValidator(null, null, UrlValidator.ALLOW_LOCAL_URLS);

         System.out.println("----------FALSE URL TEST----------");
         boolean passed = checker.isValid(generatedURL);

         if (!passed) {
            System.out.println("TEST PASS!");
         } else {
            System.out.println("TEST FAIL!");
            System.out.println("URL Fail: " + generatedURL);
         }
      }
      System.out.println("Random Testing for False Test End");
   }
}
