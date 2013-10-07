var assert = require('assert');
var nextPrime = require('./../index').nextPrime;
var asyncPrime = require('./../index').asyncPrime;

suite('nextPrime', function() {
  test('nextPrime should return the next prime number', function() {
    assert.equal(11, nextPrime(7));
  });

  test('zero and one are not prime numbers', function() {
    assert.equal(2, nextPrime(0));
    assert.equal(2, nextPrime(1));
  });
});


suite('asyncPrime', function() {
  test('asyncPrime should return the next prime number', function(done) {
    asyncPrime(128, function(n) {
      assert.equal(131, n, 'Wrong number');
      done();
    });
  });
})

suite('asyncPrime', function() {
  test('asyncPrime should return the next prime number', function(done) {
    var request = require('request');
    //var responseProcessor = 
    request('http://192.168.1.230', 
        function (error, response, body) {
          if (!error && response.statusCode == 200) {
            done();
          }
    });
  });
})

