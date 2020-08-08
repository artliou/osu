
import junit.framework.TestCase;
import java.security.*;
import java.util.Random;

public class UrlValidatorTest extends TestCase {

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
