/*


  OK, ya ready for some fun? HTML + CSS styling + javascript all in and undebuggable environment

  one trick I've learned to how to debug HTML and CSS code.

  get all your HTML code (from html to /html) and past it into this test site
  muck with the HTML and CSS code until it's what you want
  https://www.w3schools.com/html/tryit.asp?filename=tryhtml_intro

  No clue how to debug javascrip other that write, compile, upload, refresh, guess, repeat

  I'm using class designators to set styles and id's for data updating
  for example:
  the CSS class .tabledata defines with the cell will look like
  <td><div class="tabledata" id = "switch"></div></td>

  the XML code will update the data where id = "switch"
  java script then uses getElementById
  document.getElementById("switch").innerHTML="Switch is OFF";


  .. now you can have the class define the look AND the class update the content, but you will then need
  a class for every data field that must be updated, here's what that will look like
  <td><div class="switch"></div></td>

  the XML code will update the data where class = "switch"
  java script then uses getElementsByClassName
  document.getElementsByClassName("switch")[0].style.color=text_color;


  the main general sections of a web page are the following and used here

  <html>
    <style>
    // dump CSS style stuff in here
    </style>
    <body>
      <header>
      // put header code for cute banners here
      </header>
      <main>
      // the buld of your web page contents
      </main>
      <footer>
      // put cute footer (c) 2021 xyz inc type thing
      </footer>
    </body>
    <script>
    // you java code between these tags
    </script>
  </html>

//https://cdn.jsdelivr.net/npm/chart.js
myChart.update();
*/

// note R"KEYWORD( html page code )KEYWORD"; 
// again I hate strings, so char is it and this method let's us write naturally

const char PAGE_MAIN[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en" class="js-focus-visible">

<head>
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<meta charset="UTF-8">
<title>Web Page Update Demo</title>

<style>
table {
      position: relative;
      width:100%;
      border-spacing: 0px;
    }
    tr {
      border: 1px solid white;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
    }
    th {
      height: 20px;
      padding: 3px 15px;
      background-color: #343a40;
      color: #FFFFFF !important;
      }
    td {
      height: 20px;
       padding: 3px 15px;
    }
    .tabledata {
      font-size: 24px;
      position: relative;
      padding-left: 5px;
      padding-top: 5px;
      height:   25px;
      border-radius: 5px;
      color: #FFFFFF;
      line-height: 20px;
      transition: all 200ms ease-in-out;
      background-color: #00AA00;
    }
    .fanrpmslider {
      width: 30%;
      height: 55px;
      outline: none;
      height: 25px;
    }
    .bodytext {
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 24px;
      text-align: left;
      font-weight: light;
      border-radius: 5px;
      display:inline;
    }
    .navbar {
      width: 100%;
      height: 50px;
      margin: 0;
      padding: 10px 0px;
      background-color: #FFF;
      color: #000000;
      border-bottom: 5px solid #293578;
    }
    .fixed-top {
      position: fixed;
      top: 0;
      right: 0;
      left: 0;
      z-index: 1030;
    }
    .navtitle {
      float: left;
      height: 50px;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 50px;
      font-weight: bold;
      line-height: 50px;
      padding-left: 20px;
    }
   .navheading {
     position: fixed;
     left: 60%;
     height: 50px;
     font-family: "Verdana", "Arial", sans-serif;
     font-size: 20px;
     font-weight: bold;
     line-height: 20px;
     padding-right: 20px;
   }
   .navdata {
      justify-content: flex-end;
      position: fixed;
      left: 70%;
      height: 50px;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
      font-weight: bold;
      line-height: 20px;
      padding-right: 20px;
   }
    .category {
      font-family: "Verdana", "Arial", sans-serif;
      font-weight: bold;
      font-size: 32px;
      line-height: 50px;
      padding: 20px 10px 0px 10px;
      color: #000000;
    }
    .heading {
      font-family: "Verdana", "Arial", sans-serif;
      font-weight: normal;
      font-size: 28px;
      text-align: left;
    }
  
    .btn {
      background-color: #444444;
      border: none;
      color: white;
      padding: 10px 20px;
      text-align: center;
      text-decoration: none;
      display: inline-block;
      font-size: 16px;
      margin: 4px 2px;
      cursor: pointer;
    }
    .foot {
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
      position: relative;
      height:   30px;
      text-align: center;   
      color: #AAAAAA;
      line-height: 20px;
    }
    .container {
      max-width: 1800px;
      margin: 0 auto;
    }
    table tr:first-child th:first-child {
      border-top-left-radius: 5px;
    }
    table tr:first-child th:last-child {
      border-top-right-radius: 5px;
    }
    table tr:last-child td:first-child {
      border-bottom-left-radius: 5px;
    }
    table tr:last-child td:last-child {
      border-bottom-right-radius: 5px;
    }

    .chart {
        border: 1px solid #ccc;
        width: 300px;
        height: 200px;
        position: relative;
    }
    .bar {
        background-color: #007bff;
        width: 10px; /* Width of each bar */
        position: absolute;
        bottom: 0;
    }

    //HEH bars
    .bar1 { left: 10px; }
    .bar2 { left: 10px; }
    .bar3 { left: 20px; }
    .bar4 { left: 30px; }
    .bar5 { left: 40px; }
    .bar6 { left: 50px; }
    .bar7 { left: 60px; }
    .bar8 { left: 70px; }
    .bar9 { left: 80px; }
    .bar10 { left:90px; }
    .bar11 { left: 100px; }
    .bar12 { left: 110px; }
    .bar13 { left: 120px; }
    .bar14 { left: 130px; }
    .bar15 { left: 140px; }
    .bar16 { left: 150px; }
    .bar17 { left: 160px; }
    .bar18 { left: 170px; }
    .bar19 { left: 180px; }
    .bar20 { left: 190px; }
    .bar21 { left: 200px; }
    .bar22 { left: 210px; }
    .bar23 { left: 220px; }
    .bar24 { left: 230px; }
    .bar25 { left: 240px; }
    .bar26 { left: 250px; }
    .bar27 { left: 260px; }
    .bar28 { left: 270px; }
    .bar29 { left: 280px; }
    .bar30 { left: 290px; }
  </style>
</head>

  <body style="background-color: #efefef" onload="process()">
  
    <header>
      <div class="navbar fixed-top">
          <div class="container">
            <div class="navtitle">Sensor Monitor</div>
            <div class="navdata" id = "date">mm/dd/yyyy</div>
            <div class="navheading">DATE</div><br>
            <div class="navdata" id = "time">00:00:00</div>
            <div class="navheading">TIME</div>
            
          </div>
      </div>
    </header>
  
    <main class="container" style="margin-top:70px">
      <div class="category">Sensor Readings</div>
      <div style="border-radius: 10px !important;">
      <table style="width:50%">
      <colgroup>
        <col span="1" style="background-color:rgb(230,230,230); width: 20%; color:#000000 ;">
        <col span="1" style="background-color:rgb(200,200,200); width: 15%; color:#000000 ;">
        <col span="1" style="background-color:rgb(180,180,180); width: 15%; color:#000000 ;">
      </colgroup>
      <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
      <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
      <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
      <tr>
        <th colspan="1"><div class="heading">Pin</div></th>
        <th colspan="1"><div class="heading">Bits</div></th>
      </tr>
      <tr>
        <td><div class="bodytext">Pressure</div></td>
        <td><div class="tabledata" id = "b0"></div></td>
      </tr>
      <tr>
        <td><div class="bodytext">Temperature</div></td>
        <td><div class="tabledata" id = "b1"></div></td>
      </tr>
      </table>
    </div>

  <div class="chart">
    <div class="bar bar1" style="height: 0;"></div>
    <div class="bar bar2" style="height: 0;"></div>
    <div class="bar bar3" style="height: 0;"></div>
    <div class="bar bar4" style="height: 0;"></div>
    <div class="bar bar5" style="height: 0;"></div>
    <div class="bar bar6" style="height: 0;"></div>
    <div class="bar bar7" style="height: 0;"></div>
    <div class="bar bar8" style="height: 0;"></div>
    <div class="bar bar9" style="height: 0;"></div>
    <div class="bar bar10" style="height: 0;"></div>
    <div class="bar bar11" style="height: 0;"></div>
    <div class="bar bar12" style="height: 0;"></div>
    <div class="bar bar13" style="height: 0;"></div>
    <div class="bar bar14" style="height: 0;"></div>
    <div class="bar bar15" style="height: 0;"></div>
    <div class="bar bar16" style="height: 0;"></div>
    <div class="bar bar17" style="height: 0;"></div>
    <div class="bar bar18" style="height: 0;"></div>
    <div class="bar bar19" style="height: 0;"></div>
    <div class="bar bar20" style="height: 0;"></div>
    <div class="bar bar21" style="height: 0;"></div>
    <div class="bar bar22" style="height: 0;"></div>
    <div class="bar bar23" style="height: 0;"></div>
    <div class="bar bar24" style="height: 0;"></div>
    <div class="bar bar25" style="height: 0;"></div>
    <div class="bar bar26" style="height: 0;"></div>
    <div class="bar bar27" style="height: 0;"></div>
    <div class="bar bar28" style="height: 0;"></div>
    <div class="bar bar29" style="height: 0;"></div>
    <div class="bar bar30" style="height: 0;"></div>
</div>

    
  </main>

    <footer div class="foot" id = "temp" >ESP32 Web Page Creation and Data Update Demo</div></footer>

  </body>


  <script type = "text/javascript">

  var data = [];

  function updateBarHeights() {
// Select each bar and set its height according to data values
    var bars = document.querySelectorAll('.bar');
    bars.forEach((bar, index) => {
      bar.style.height = `${data[index]}px`;
    });
}
  
    // global variable visible to all java functions
    var xmlHttp=createXmlHttpObject();

    // function to create XML object
    function createXmlHttpObject(){
      if(window.XMLHttpRequest){
        xmlHttp=new XMLHttpRequest();
      }
      else{
        xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");
      }
      return xmlHttp;
    }
	

// Function to update pressure readings and shift previous values
function updatePressureReadings(newReading) {

    var maxData = 2000;
    var maxHeight = 200;

    var result1 = (newReading / maxData) * maxHeight;
    var result2 = Math.floor(result1);

    // Add the new reading to the beginning of the array
    data.unshift(result2);
    
    // Remove the oldest reading if the array length exceeds
    if (data.length > 30) {
        data.pop();
    }
}


    // function to handle the response from the ESP XML BOI
    function response(){
      var message;
      var barwidth;
      var currentsensor;
      var xmlResponse;
      var xmldoc;
      var dt = new Date();
      var color = "#e8e8e8";
     
      // get the xml stream
      xmlResponse=xmlHttp.responseXML;
  
      // get host date and time
      document.getElementById("time").innerHTML = dt.toLocaleTimeString();
      document.getElementById("date").innerHTML = dt.toLocaleDateString();
  
      // Pressure
      xmldoc = xmlResponse.getElementsByTagName("Pressure"); //bits for Pressure
      message = xmldoc[0].firstChild.nodeValue;
      
      if (message > 2048){
      color = "#aa0000";
      }
      else {
        color = "#0000aa";
      }

      updatePressureReadings(message);
      updateBarHeights();
      
      barwidth = message / 4060;
      document.getElementById("b0").innerHTML=message;
      document.getElementById("b0").style.width=(barwidth+"%");
      // if you want to use global color set above in <style> section
      // other wise uncomment and let the value dictate the color
      //document.getElementById("b0").style.backgroundColor=color;
      //document.getElementById("b0").style.borderRadius="5px";
	  
	   message = parseInt(message);
	  
      // Temperature
      xmldoc = xmlResponse.getElementsByTagName("Temperature");
      message = xmldoc[0].firstChild.nodeValue;
      if (message > 2048){
      color = "#aa0000";
      }
      else {
        color = "#0000aa";
      }
      document.getElementById("b1").innerHTML=message;
      width = message / 85.00;
      document.getElementById("b1").style.width=(width+"%");
      document.getElementById("b1").style.backgroundColor=color;
      //document.getElementById("b1").style.borderRadius="5px";
    }
  
  
    // general processing code for the web page to ask for an XML steam
    // this is actually why you need to keep sending data to the page to 
    // force this call with stuff like this
    // server.on("/xml", SendXML);
    // otherwise the page will not request XML from the ESP, and updates will not happen
    function process(){
     
     if(xmlHttp.readyState==0 || xmlHttp.readyState==4) {
        xmlHttp.open("PUT","xml",true);
        xmlHttp.onreadystatechange=response;
        xmlHttp.send(null);
      }       
        // you may have to play with this value, big pages need more porcessing time, and hence
        // a longer timeout
        setTimeout("process()",100);
    }
	
	
	// get it? here's the xml message example:
	//<?xml version="1.0" encoding="UTF-8"?>
	//		<Pressure>1500</Pressure>
	//	<data>
	//		<Temperature>25</Temperature>
	//	</data>

  
  
  </script>

</html>



)=====";