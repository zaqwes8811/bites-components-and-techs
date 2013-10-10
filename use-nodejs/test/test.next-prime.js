var assert = require('assert');
var _ = require('underscore');
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

suite('nextPrime', function() {
  test('nextPrime should return the next prime number', function() {
    var Person = {
      name: "Tim",
      age: 28,
      greeting: function () {
        return "Hello " + this.name + ".  Wow, you are " + this.age + " years old.";
      }
    };

    Person.greeting();

    var greeting = Person.greeting;
    // BAD!
    //console.log(greeting()); // Will get undefined for `this.name` and `this.age`
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

function OneCard(context) {
  this.context_ = context;
}
 
OneCard.prototype.exchange = function () {
  console.log(this);
}

var card = new OneCard("hello");

suite('asyncPrime', function() {
  test('asyncPrime should return the next prime number', function(done) {
    var request = require('request');
    
    var responseProcessor = _.bind(card.exchange, card)
    //responseProcessor = card.exchange;  // bad!
    request('http://192.168.1.230', 
        function (error, response, body) {
          if (!error && response.statusCode == 200) {
            responseProcessor();
            card.exchange();
            done();
          }
    });
  });
})

