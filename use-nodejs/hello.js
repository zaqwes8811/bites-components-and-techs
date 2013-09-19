// JQuery on Windows no work
// Google Closure... есть nclosure, но с Windows похоже не работает. 

console.log("Hello World");

// Constructor
function Apple (type) {
    this.type = type;
    this.color = "red";
    this.getInfo = getAppleInfo;
}
 
// anti-pattern! keep reading...
function getAppleInfo() {
    return this.color + ' ' + this.type + ' apple';
}

var apple = new Apple('macintosh');
apple.color = "reddish";
console.log(apple.getInfo());

// Better
function AppleBetter (type) {
  this.type = type;
  this.color = "red";
  this.getInfo = function () {
    return this.color + ' ' + this.type + ' apple';
  };
}

var apple = new AppleBetter('macintosh');
apple.color = "reddish";
console.log(apple.getInfo());

// Prototype
function AppleProto (type) {
    this.type = type;
    this.color = "red";
}
 
AppleProto.prototype.getInfo = function() {
    return this.color + ' ' + this.type + ' apple';
};

var apple = new AppleProto('macintosh');
apple.color = "reddish";
console.log(apple.getInfo());


// 2 WAY
var apple = {
    type: "macintosh",
    color: "red",
    getInfo: function () {
        return this.color + ' ' + this.type + ' apple';
    }
}

console.log(apple.getInfo());

// nclosure
// You can now run the test just by executing this file
require('nclosure').nclosure();

goog.require('goog.testing.jsunit');
// Import the code you are testing (may need an additionalDeps defined)
goog.require('nclosure.examples.simple.Example');

// Any testXXX function are auto-discovered and run
var testFunction1 = function() {
  assertNotEquals(typeof(example_), 'undefined');
};

// Also auto discovered
function testFunction2() {
  assertTrue(false);
}





