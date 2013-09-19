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


for(var i=0;i<50;i++) {
      functionWrappingAsycfuncs(i)
}

var nums = [0,1...50]
nums.forEach(functionWrappingAsyncfuns)

functionWrappingAsycfuncs(i){
  readFileAsync(i,function(){
    console.log(i);
  });
}




