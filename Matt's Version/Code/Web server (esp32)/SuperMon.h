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

	.Charts {
	  width: 100%;
      height: 500px;
      display: flex;
    }

    .Wchart {
        border: 1px solid #ccc;
        width: 450px;
        height: 100%;
        position: relative;
    }
	
	.Pchart {
        border: 1px solid #ccc;
        width: 450px;
        height: 100%;
        position: relative;
    }
	
    .bar {
        background-color: #4db74a;
        width: 5px; /* Width of each bar */
        position: absolute;
        bottom: 0;
    }
	
	.barw {
        background-color: #007bff;
        width: 5px; /* Width of each bar */
        position: absolute;
        bottom: 0;
    }

    .barA {
        background-color: #FF0000;
        width: 5px; /* Width of each bar */
        position: absolute;
        bottom: 0;
    }

    .barAB { left: 300px; }

    //HEH bars
    .bar1 { left: 1%; }
    .bar2 { left: 1%; }
    .bar3 { left: 2%; }
    .bar4 { left: 3%; }
    .bar5 { left: 4%; }
    .bar6 { left: 5%; }
    .bar7 { left: 6%; }
    .bar8 { left: 7%; }
    .bar9 { left: 8%; }
    .bar10 { left:9%; }
    .bar11 { left: 10%; }
    .bar12 { left: 11%; }
    .bar13 { left: 12%; }
    .bar14 { left: 13%; }
    .bar15 { left: 14%; }
    .bar16 { left: 15%; }
    .bar17 { left: 16%; }
    .bar18 { left: 17%; }
    .bar19 { left: 18%; }
    .bar20 { left: 19%; }
    .bar21 { left: 20%; }
    .bar22 { left: 21%; }
    .bar23 { left: 22%; }
    .bar24 { left: 23%; }
    .bar25 { left: 24%; }
    .bar26 { left: 25%; }
    .bar27 { left: 26%; }
    .bar28 { left: 27%; }
    .bar29 { left: 28%; }
    .bar30 { left: 29%; }
    .bar31 { left: 30%; }
    .bar32 { left: 31%; }
    .bar33 { left: 32%; }
    .bar34 { left: 33%; }
    .bar35 { left: 34%; }
    .bar36 { left: 35%; }
    .bar37 { left: 36%; }
    .bar38 { left: 37%; }
    .bar39 { left: 38%; }
    .bar40 { left: 39%; }
    .bar41 { left: 40%; }
    .bar42 { left: 41%; }
    .bar43 { left: 42%; }
    .bar44 { left: 43%; }
    .bar45 { left: 44%; }
    .bar46 { left: 45%; }
    .bar47 { left: 46%; }
    .bar48 { left: 47%; }
    .bar49 { left: 48%; }
    .bar50 { left: 49%; }
    .bar51 { left: 50%; }
    .bar52 { left: 51%; }
    .bar53 { left: 52%; }
    .bar54 { left: 53%; }
    .bar55 { left: 54%; }
    .bar56 { left: 55%; }
    .bar57 { left: 56%; }
    .bar58 { left: 57%; }
    .bar59 { left: 58%; }
    .bar60 { left: 59%; }
    .bar61 { left: 60%; }
    .bar62 { left: 61%; }
    .bar63 { left: 62%; }
    .bar64 { left: 63%; }
    .bar65 { left: 64%; }
    .bar66 { left: 65%; }
    .bar67 { left: 66%; }
    .bar68 { left: 67%; }
    .bar69 { left: 68%; }
    .bar70 { left: 69%; }
    .bar71 { left: 70%; }
    .bar72 { left: 71%; }
    .bar73 { left: 72%; }
    .bar74 { left: 73%; }
    .bar75 { left: 74%; }
    .bar76 { left: 75%; }
    .bar77 { left: 76%; }
    .bar78 { left: 77%; }
    .bar79 { left: 78%; }
    .bar80 { left: 79%; }
    .bar81 { left: 80%; }
    .bar82 { left: 81%; }
    .bar83 { left: 82%; }
    .bar84 { left: 83%; }
    .bar85 { left: 84%; }
    .bar86 { left: 85%; }
    .bar87 { left: 86%; }
    .bar88 { left: 87%; }
    .bar89 { left: 88%; }
    .bar90 { left: 89%; }
	.bar91 { left: 90%; }
    .bar92 { left: 91%; }
    .bar93 { left: 92%; }
    .bar94 { left: 93%; }
    .bar95 { left: 94%; }
    .bar96 { left: 95%; }
    .bar97 { left: 96%; }
    .bar98 { left: 97%; }
    .bar99 { left: 98%; }
    .bar100 { left: 99%; }
    
	
	.line {
			position: absolute;
			bottom: 0;
			width: 100%;
			height: var(--y-value);
			transition: height 0.5s ease-in-out;
			border-top: 1px solid #000000;
			font-size: 10px;
		}

    .threshold {
			position: absolute;
			bottom: 0;
			width: 100%;
			height: var(--y-value);
			transition: height 0.5s ease-in-out;
			border-top: 1px solid #FF0000;
			font-size: 10px;
		}
		
	.current {
			position: absolute;
			bottom: 0;
			width: 100%;
			height: var(--y-value);
			border-top: 1px solid ##FFFF00;
			font-size: 10px;
		}
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
        <th colspan="1"><div class="heading">Sensors</div></th>
        <th colspan="1"><div class="heading">Data</div></th>
      </tr>
      <tr>
        <td><div class="bodytext">Pressure</div></td>
        <td><div class="tabledata" id = "b0"></div></td>
      </tr>
	  <tr>
        <td><div class="bodytext">Water Height</div></td>
        <td><div class="tabledata" id = "w0"></div></td>
      </tr>
      <tr>
        <td><div class="bodytext">Temperature</div></td>
        <td><div class="tabledata" id = "b1"></div></td>
      </tr>
      </table>
    </div>
	
	<div>
	
	<div class="category">Charts</div>
	
	<table style="width:905px">
	<colgroup>
        <col span="1" style="background-color:rgb(230,230,230); width: 50%; color:#000000 ;">
        <col span="1" style="background-color:rgb(200,200,200); width: 50%%; color:#000000 ;">
      </colgroup>
	<col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
    <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
    <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
		<tr>
			<th colspan="1"><div class="heading">Pressure (hpa)</div></th>
			<th colspan="1"><div class="heading">Water Height (cm)</div></th>
		</tr>
	</table>
</div>
	
<div class="Charts">

  <div class="Wchart">
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
    <div class="bar bar31" style="height: 0;"></div>
    <div class="bar bar32" style="height: 0;"></div>
    <div class="bar bar33" style="height: 0;"></div>
    <div class="bar bar34" style="height: 0;"></div>
    <div class="bar bar35" style="height: 0;"></div>
    <div class="bar bar36" style="height: 0;"></div>
    <div class="bar bar37" style="height: 0;"></div>
    <div class="bar bar38" style="height: 0;"></div>
    <div class="bar bar39" style="height: 0;"></div>
    <div class="bar bar40" style="height: 0;"></div>
    <div class="bar bar41" style="height: 0;"></div>
    <div class="bar bar42" style="height: 0;"></div>
    <div class="bar bar43" style="height: 0;"></div>
    <div class="bar bar44" style="height: 0;"></div>
    <div class="bar bar45" style="height: 0;"></div>
    <div class="bar bar46" style="height: 0;"></div>
    <div class="bar bar47" style="height: 0;"></div>
    <div class="bar bar48" style="height: 0;"></div>
    <div class="bar bar49" style="height: 0;"></div>
    <div class="bar bar50" style="height: 0;"></div>
    <div class="bar bar51" style="height: 0;"></div>
    <div class="bar bar52" style="height: 0;"></div>
    <div class="bar bar53" style="height: 0;"></div>
    <div class="bar bar54" style="height: 0;"></div>
    <div class="bar bar55" style="height: 0;"></div>
    <div class="bar bar56" style="height: 0;"></div>
    <div class="bar bar57" style="height: 0;"></div>
    <div class="bar bar58" style="height: 0;"></div>
    <div class="bar bar59" style="height: 0;"></div>
    <div class="bar bar60" style="height: 0;"></div>
	<div class="bar bar61" style="height: 0;"></div>
    <div class="bar bar62" style="height: 0;"></div>
    <div class="bar bar63" style="height: 0;"></div>
    <div class="bar bar64" style="height: 0;"></div>
    <div class="bar bar65" style="height: 0;"></div>
    <div class="bar bar66" style="height: 0;"></div>
    <div class="bar bar67" style="height: 0;"></div>
    <div class="bar bar68" style="height: 0;"></div>
    <div class="bar bar69" style="height: 0;"></div>
    <div class="bar bar70" style="height: 0;"></div>
    <div class="bar bar71" style="height: 0;"></div>
    <div class="bar bar72" style="height: 0;"></div>
    <div class="bar bar73" style="height: 0;"></div>
    <div class="bar bar74" style="height: 0;"></div>
    <div class="bar bar75" style="height: 0;"></div>
    <div class="bar bar76" style="height: 0;"></div>
    <div class="bar bar77" style="height: 0;"></div>
    <div class="bar bar78" style="height: 0;"></div>
    <div class="bar bar79" style="height: 0;"></div>
    <div class="bar bar80" style="height: 0;"></div>
    <div class="bar bar81" style="height: 0;"></div>
    <div class="bar bar82" style="height: 0;"></div>
    <div class="bar bar83" style="height: 0;"></div>
    <div class="bar bar84" style="height: 0;"></div>
    <div class="bar bar85" style="height: 0;"></div>
    <div class="bar bar86" style="height: 0;"></div>
    <div class="bar bar87" style="height: 0;"></div>
    <div class="bar bar88" style="height: 0;"></div>
    <div class="bar bar89" style="height: 0;"></div>
    <div class="bar bar90" style="height: 0;"></div>
	<div class="bar bar91" style="height: 0;"></div>
    <div class="bar bar92" style="height: 0;"></div>
    <div class="bar bar93" style="height: 0;"></div>
    <div class="bar bar94" style="height: 0;"></div>
    <div class="bar bar95" style="height: 0;"></div>
    <div class="bar bar96" style="height: 0;"></div>
    <div class="bar bar97" style="height: 0;"></div>
    <div class="bar bar98" style="height: 0;"></div>
    <div class="bar bar99" style="height: 0;"></div>
    <div class="bar bar100" style="height: 0;"></div>
    <div class="barA barAB" style="height: 0;"></div>

    <div class="line" style="--y-value: 100%;">2000</div>
    <div class="line" style="--y-value: 75%;">1500</div>
    <div class="line" style="--y-value: 50%;">1000</div>
    <div class="line" style="--y-value: 25%;">500</div>
    
    <div class="threshold" id="PlineElement"></div>
</div>

<div class="Pchart">
    <div class="barw bar1" style="height: 0;"></div>
    <div class="barw bar2" style="height: 0;"></div>
    <div class="barw bar3" style="height: 0;"></div>
    <div class="barw bar4" style="height: 0;"></div>
    <div class="barw bar5" style="height: 0;"></div>
    <div class="barw bar6" style="height: 0;"></div>
    <div class="barw bar7" style="height: 0;"></div>
    <div class="barw bar8" style="height: 0;"></div>
    <div class="barw bar9" style="height: 0;"></div>
    <div class="barw bar10" style="height: 0;"></div>
    <div class="barw bar11" style="height: 0;"></div>
    <div class="barw bar12" style="height: 0;"></div>
    <div class="barw bar13" style="height: 0;"></div>
    <div class="barw bar14" style="height: 0;"></div>
    <div class="barw bar15" style="height: 0;"></div>
    <div class="barw bar16" style="height: 0;"></div>
    <div class="barw bar17" style="height: 0;"></div>
    <div class="barw bar18" style="height: 0;"></div>
    <div class="barw bar19" style="height: 0;"></div>
    <div class="barw bar20" style="height: 0;"></div>
    <div class="barw bar21" style="height: 0;"></div>
    <div class="barw bar22" style="height: 0;"></div>
    <div class="barw bar23" style="height: 0;"></div>
    <div class="barw bar24" style="height: 0;"></div>
    <div class="barw bar25" style="height: 0;"></div>
    <div class="barw bar26" style="height: 0;"></div>
    <div class="barw bar27" style="height: 0;"></div>
    <div class="barw bar28" style="height: 0;"></div>
    <div class="barw bar29" style="height: 0;"></div>
    <div class="barw bar30" style="height: 0;"></div>
    <div class="barw bar31" style="height: 0;"></div>
    <div class="barw bar32" style="height: 0;"></div>
    <div class="barw bar33" style="height: 0;"></div>
    <div class="barw bar34" style="height: 0;"></div>
    <div class="barw bar35" style="height: 0;"></div>
    <div class="barw bar36" style="height: 0;"></div>
    <div class="barw bar37" style="height: 0;"></div>
    <div class="barw bar38" style="height: 0;"></div>
    <div class="barw bar39" style="height: 0;"></div>
    <div class="barw bar40" style="height: 0;"></div>
    <div class="barw bar41" style="height: 0;"></div>
    <div class="barw bar42" style="height: 0;"></div>
    <div class="barw bar43" style="height: 0;"></div>
    <div class="barw bar44" style="height: 0;"></div>
    <div class="barw bar45" style="height: 0;"></div>
    <div class="barw bar46" style="height: 0;"></div>
    <div class="barw bar47" style="height: 0;"></div>
    <div class="barw bar48" style="height: 0;"></div>
    <div class="barw bar49" style="height: 0;"></div>
    <div class="barw bar50" style="height: 0;"></div>
    <div class="barw bar51" style="height: 0;"></div>
    <div class="barw bar52" style="height: 0;"></div>
    <div class="barw bar53" style="height: 0;"></div>
    <div class="barw bar54" style="height: 0;"></div>
    <div class="barw bar55" style="height: 0;"></div>
    <div class="barw bar56" style="height: 0;"></div>
    <div class="barw bar57" style="height: 0;"></div>
    <div class="barw bar58" style="height: 0;"></div>
    <div class="barw bar59" style="height: 0;"></div>
    <div class="barw bar60" style="height: 0;"></div>
	<div class="barw bar61" style="height: 0;"></div>
    <div class="barw bar62" style="height: 0;"></div>
    <div class="barw bar63" style="height: 0;"></div>
    <div class="barw bar64" style="height: 0;"></div>
    <div class="barw bar65" style="height: 0;"></div>
    <div class="barw bar66" style="height: 0;"></div>
    <div class="barw bar67" style="height: 0;"></div>
    <div class="barw bar68" style="height: 0;"></div>
    <div class="barw bar69" style="height: 0;"></div>
    <div class="barw bar70" style="height: 0;"></div>
    <div class="barw bar71" style="height: 0;"></div>
    <div class="barw bar72" style="height: 0;"></div>
    <div class="barw bar73" style="height: 0;"></div>
    <div class="barw bar74" style="height: 0;"></div>
    <div class="barw bar75" style="height: 0;"></div>
    <div class="barw bar76" style="height: 0;"></div>
    <div class="barw bar77" style="height: 0;"></div>
    <div class="barw bar78" style="height: 0;"></div>
    <div class="barw bar79" style="height: 0;"></div>
    <div class="barw bar80" style="height: 0;"></div>
    <div class="barw bar81" style="height: 0;"></div>
    <div class="barw bar82" style="height: 0;"></div>
    <div class="barw bar83" style="height: 0;"></div>
    <div class="barw bar84" style="height: 0;"></div>
    <div class="barw bar85" style="height: 0;"></div>
    <div class="barw bar86" style="height: 0;"></div>
    <div class="barw bar87" style="height: 0;"></div>
    <div class="barw bar88" style="height: 0;"></div>
    <div class="barw bar89" style="height: 0;"></div>
    <div class="barw bar90" style="height: 0;"></div>
	<div class="barw bar90" style="height: 0;"></div>
	<div class="barw bar91" style="height: 0;"></div>
    <div class="barw bar92" style="height: 0;"></div>
    <div class="barw bar93" style="height: 0;"></div>
    <div class="barw bar94" style="height: 0;"></div>
    <div class="barw bar95" style="height: 0;"></div>
    <div class="barw bar96" style="height: 0;"></div>
    <div class="barw bar97" style="height: 0;"></div>
    <div class="barw bar98" style="height: 0;"></div>
    <div class="barw bar99" style="height: 0;"></div>
    <div class="barw bar100" style="height: 0;"></div>
    <div class="barA barAB" style="height: 0;"></div>

    <div class="line" style="--y-value: 100%;">15</div>
    <div class="line" style="--y-value: 75%;">7.5</div>
    <div class="line" style="--y-value: 50%;">0</div>
    <div class="line" style="--y-value: 25%;">-7.5</div>
    
    <div class="threshold" id="WlineElement"></div>
	<div class="current" id="WClineElement"></div>
</div>

<div>

  <table style="width: 0%; height: 100%">
    <colgroup>
      <col span="1" style="background-color:rgb(230,230,230); width: 1%; color:#000000 ; height: 16%;">
      <col span="1" style="background-color:rgb(200,200,200); width: 1%; color:#000000 ; height: 16%;">
      <col span="1" style="background-color:rgb(180,180,180); width: 1%; color:#000000 ; height: 16%;">
    </colgroup>
      <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
      <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
      <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
    <tr>
      <td colspan="1"><label for="PinputField">Threshold Pressure:</label></td>
      <td colspan="1"><input type="text" id="PinputField"></td>
      <td colspan="1"><button onclick="PdisplayInput()">Submit</button></td>
    </tr>
    
	<tr>
      <td colspan="1"><label for="WinputField">Threshold Water Height:</label></td>
      <td colspan="1"><input type="text" id="WinputField"></td>
      <td colspan="1"><button onclick="WdisplayInput()">Submit</button></td>
    </tr>
	
	<tr>
      <td colspan="1"><label for="BinputField">Base Pressure:</label></td>
      <td colspan="1"><input type="text" id="BinputField"></td>
      <td colspan="1"><button onclick="BdisplayInput()">Submit</button></td>
  </tr>
	
    <tr>
      <td>Threshold</td>
      <td><div id="PdisplayDiv"></div></td>
      <td>(hPa)</td>
    </tr> 
  
	<tr>
      <td>Wave height</td>
      <td><div id="WdisplayDiv"></div></td>
      <td>(cm)</td>
    </tr> 
	
	<tr>
      <td>Base Pressure</td>
      <td><div id="BdisplayDiv"></div></td>
      <td>(hPa)</td>
    </tr> 
  
  </table>
</div>


</div>
  </main>

    <footer div class="foot" id = "temp" >ESP32 Web Page Creation and Data Update Demo</div></footer>

  </body>


  <script type = "text/javascript">
  var Pdata = [];
  var PmaxData = 2000;
  var Pthreshold = 0;
  var PthresholdPercentage = 0; // Initialize

  var Wdata = [];
  var WmaxData = 30;
  var Wthreshold = 0;
  var WthresholdPercentage = 0; // Initialize
  var Base = 1000;
  var Density = 1000; // Density in kg/m^3
  var Gravity = 9.81;
	
  var userInputAsNumber = 0;
  var waterLevel = WmaxData / 2;

	//debugging 
	
	/*
	
	var Pdata = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100];
    var Wdata = [100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1];
	
	//PupdatePressureReadings(1000);
	//WupdatePressureReadings(1000);
	
	WupdateBarHeights();
	PupdateBarHeights();
	
	*/
	
  function BdisplayInput() {
		var userInput = document.getElementById("BinputField").value;
		
		var inputNumber = parseFloat(userInput);
		// Check if the parsed input is a valid number
		if (!isNaN(inputNumber)) {
			Base = inputNumber;
		}
		document.getElementById("BdisplayDiv").innerHTML = Base;
  }	
	
  function PdisplayInput() {
            // Get the value entered by the user
            var userInput = document.getElementById("PinputField").value;
            
            // Parse the user input as a float
            var inputNumber = parseFloat(userInput);
            
            // Check if the parsed input is a valid number
            if (!isNaN(inputNumber)) {
                // If it's a valid number, add it to the existing total

                //processed for bar threshold
				threshold = inputNumber;
				//Pressure
                Pthreshold = threshold;
                PthresholdPercentage = (inputNumber/PmaxData) * 100;
                PthresholdPercentage = Math.floor(PthresholdPercentage);
                userInputAsNumber = Math.floor(userInputAsNumber);
				
				//Height
				Wthreshold = 100 * (threshold - Base) / (Density * Gravity);
				WthresholdPercentage = Wthreshold + waterLevel;
				WthresholdPercentage = (WthresholdPercentage / WmaxData) * 100;
				WthresholdPercentage = Math.floor(WthresholdPercentage);
				
            }
            // Update the display div with the updated total
            document.getElementById("PdisplayDiv").innerHTML = Pthreshold;
            document.getElementById("PlineElement").style.setProperty("--y-value", PthresholdPercentage + "%");
            document.getElementById("PlineElement").innerHTML = Pthreshold;
			
			document.getElementById("WdisplayDiv").innerHTML = Wthreshold;
			document.getElementById("WlineElement").style.setProperty("--y-value", WthresholdPercentage + "%");
            document.getElementById("WlineElement").innerHTML = Wthreshold;
			
			UpdateThreshold(Pthreshold);
        }
		
  function WdisplayInput() {
			// Get the value entered by the user
            var userInput = document.getElementById("WinputField").value;
            
            // Parse the user input as a float
            var inputNumber = parseFloat(userInput);
            
            // Check if the parsed input is a valid number
            if (!isNaN(inputNumber)) {
                // If it's a valid number, add it to the existing total
				threshold = inputNumber;
				
				//pressure
				Pthreshold = ((threshold / 100) * (Density * Gravity)) + Base;
				PthresholdPercentage = (Pthreshold / PmaxData) * 100;
				PthresholdPercentage = Math.floor(PthresholdPercentage);
				
				//height
				Wthreshold = threshold;
				WthresholdPercentage = Wthreshold + waterLevel;
				WthresholdPercentage = (WthresholdPercentage / WmaxData) * 100;
				WthresholdPercentage = Math.floor(WthresholdPercentage);
			}
			// Update the display div with the updated total
            document.getElementById("PdisplayDiv").innerHTML = Pthreshold;
            document.getElementById("PlineElement").style.setProperty("--y-value", PthresholdPercentage + "%");
            document.getElementById("PlineElement").innerHTML = Pthreshold;
			
			document.getElementById("WdisplayDiv").innerHTML = Wthreshold;
			document.getElementById("WlineElement").style.setProperty("--y-value", WthresholdPercentage + "%");
            document.getElementById("WlineElement").innerHTML = Wthreshold;
			
			UpdateThreshold(Pthreshold);
   }

  function UpdateThreshold(value) {
      var xhttp = new XMLHttpRequest();
      xhttp.open("PUT", "UPDATE_THRESHOLD?VALUE="+value, true);
      xhttp.send();
    }

  function PupdateBarHeights() {
// Select each bar and set its height according to data values
    var bars = document.querySelectorAll('.bar');
    bars.forEach((bar, index) => {
      bar.style.height = `${Pdata[index]}%`;
    });
}
  
  function WupdateBarHeights() {
// Select each bar and set its height according to data values
    var bars = document.querySelectorAll('.barw');
    bars.forEach((bar, index) => {
      bar.style.height = `${Wdata[index]}%`;
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
function PupdatePressureReadings(newReading) {

    result = (newReading / PmaxData) * 100;
    result = Math.floor(result);

    // Add the new reading to the beginning of the array
    Pdata.unshift(result);
    
    // Remove the oldest reading if the array length exceeds
    if (Pdata.length > 90) {
        Pdata.pop();
    }
}

function WupdatePressureReadings(newReading) {

	result = newReading;

    resultA = 100 * (result - Base) / (Density * Gravity);
	resultA = parseFloat(resultA.toFixed(2));
	resultB = resultA + waterLevel;
	
	result1 = (resultB / WmaxData) * 100;
	result1 = Math.floor(result1);
	
	document.getElementById("WClineElement").style.setProperty("--y-value", result1 + "%");
    document.getElementById("WClineElement").innerHTML = resultA;
	document.getElementById("w0").innerHTML = resultA;

    // Add the new reading to the beginning of the array
    Wdata.unshift(result1);
    
    // Remove the oldest reading if the array length exceeds
    if (Wdata.length > 90) {
        Wdata.pop();
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

      PupdatePressureReadings(message);
	  WupdatePressureReadings(message);
      PupdateBarHeights();
      WupdateBarHeights();
	  
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
        setTimeout("process()",50);
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