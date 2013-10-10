function assert(expr, msg) {
  if (!expr) throw new Error(msg || 'failed');
}
 
describe("Mocha Ajax Tests", function(){  
  var flag = false;   
  beforeEach(function(done){     
     setTimeout(function(){      
       flag = true;       
        
       // complete the async beforeEach      
       done();     
     }, 500);   
  });   
   
  it("flag should be true", function(){    
    assert(flag === true);  
  }); 
});