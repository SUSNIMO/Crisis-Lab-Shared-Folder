const char PAGE_MAIN[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en" class="js-focus-visible">

<head>
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<meta charset="UTF-8">
	<title>Tsunami Wave Data Page</title>

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
		  width: 1700px;
		  height: 400px;
		  display: flex;
		  border: 1px solid black;
		}

		.Pchart {
			display: flex;
			align-items: flex-end;
			width: 30%;
			height: 100%;
			border-left: 2px solid black;
			border-bottom: 2px solid black;	
		}
		.Wchart {
			display: flex;
			align-items: flex-end;
			width: 30%;
			height: 100%;
			border-left: 2px solid black;
		}

		.Pbar {
			width: 1%;
			background-color: #32CD32;
			display: flex;
			align-items: flex-end;        
		}
				
		.Wbar {
			width: 1%;
			background-color: #0000FF;
			display: flex;
			align-items: flex-end;        
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
			
		#popupOverlay {
			display: none;
			position: fixed;
			top: 0;
			left: 0;
			width: 100%;
			height: 100%;
			background-color: rgba(0, 0, 0, 0.5);
			z-index: 1000;
		}

		#popupContent {
			width: 600px;
			height: 600px;
			position: absolute;
			top: 50%;
			left: 80%;
			transform: translate(-50%, -50%);
			padding: 20px;
			background-color: white;
			border-radius: 5px;
			box-shadow: 0 0 10px rgba(0, 0, 0, 0.25);
			font-size: 50px;
		}

		#closeButton {
			width: 25%;
			height: 10%;
			font-size: 25px;
			margin-top: 10px;
			padding: 5px 10px;
			background-color: #f44336;
			color: white;
			border: none;
			border-radius: 3px;
			cursor: pointer;
		}
			
		#WaterChart, #PressureChart {
			position: relative;
			width: 100%; 
			height: 100%; 
			border: 1px solid black; 
		}

		.marker {
			width: 100%;
			position: absolute;
			left: 0;
			right: 0;
			border-top: 1px dashed gray; /* Dashed line for marker */
			font-size: 10px;
			color: black;
		}

		.thresholdMarker {
			width: 100%;
			position: absolute;
			left: 0;
			right: 0;
			border-top: 1px solid red; /* Dashed line for marker */
			text-align: right;
			padding-right: 5px;
			font-size: 10px;
			color: red;
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

		<div class="category">Charts</div>
	
		<div style="width: 1700px;">
			<table style="width: 67%;">
				<colgroup>
					<col span="1" style="background-color:rgb(230,230,230); width: 50%; color:#000000 ;">
					<col span="1" style="background-color:rgb(200,200,200); width: 50%; color:#000000 ;">
				</colgroup>
				<tr>
					<th colspan="1"><div class="heading">Pressure (hpa)</div></th>
					<th colspan="1"><div class="heading">Water Height (cm)</div></th>
				</tr>
			</table>
		</div>
	
		<div class="Charts">
			<div class="Pchart" id="PressureChart"></div>
			<div class="Wchart" id="WaterChart"></div>

			<div>

				<table style="width: 100%; height: 100%">
					<colgroup>
						<col span="1" style="background-color:rgb(230,230,230); width: 20%; color:#000000 ; height: 16%;">
						<col span="1" style="background-color:rgb(200,200,200); width: 60%; color:#000000 ; height: 16%;">
						<col span="1" style="background-color:rgb(180,180,180); width: 20%; color:#000000 ; height: 16%;">
					</colgroup>
					<col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
					<col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
					<col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
					<tr>
						<td colspan="1"><label for="PinputField">Threshold Pressure:</label></td>
						<td colspan="1"><input type="text" id="PinputField" style="width: 75px"></td>
						<td colspan="1"><button onclick="PdisplayInput()">Submit</button></td>
					</tr>
					
					<tr>
						<td colspan="1"><label for="WinputField">Threshold Water:</label></td>
						<td colspan="1"><input type="text" id="WinputField" style="width: 75px"></td>
						<td colspan="1"><button onclick="WdisplayInput()">Submit</button></td>
					</tr>
					
					<tr>
					  <td colspan="1"><label for="BinputField">Base Pressure:</label></td>
					  <td colspan="1"><input type="text" id="BinputField" style="width: 75px"></td>
					  <td colspan="1"><button onclick="BdisplayInput()">Submit</button></td>
					</tr>
				  
					<tr>
						<td>Alarm</td>
						<td>Test runner</td>
						<td><button onclick="showPopup()">Alarm</button></td>
					</tr>
  
					<div id="popupOverlay">
						<div id="popupContent">
							<p>Alarm is triggered</p>
							<button id="closeButton" onclick="closePopup()">Close</button>
						</div>
					</div>
  
				</table>
			</div>

			<div style="width: 20%">
				<table style="width: 100%; height: 100%">
					<colgroup>
						<col span="1" style="background-color:rgb(230,230,230); width: 20%%; color:#000000 ; height: 16%;">
						<col span="1" style="background-color:rgb(200,200,200); width: 60%; color:#000000 ; height: 16%;">
						<col span="1" style="background-color:rgb(180,180,180); width: 20%; color:#000000 ; height: 16%;">
					</colgroup>
					<col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
					<col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
					<col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
	 
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
	
	<p></p>
    
	<footer div class="foot" id = "temp" >
		<button onclick="Credits()">End Credits</button>
		</div>
	</footer>
</body>


<script type = "text/javascript">
	var Pdata = [];
	var Pthreshold;

	var Wdata = [];
	var Wthreshold;
  
	var Base = 1000;
	var Density = 1000; // Density in kg/m^3
	var Gravity = 9.81; //Gravitational acceleration
	
	var userInputAsNumber;
	var waterLevel;


	/*
	//debugging (dummy data)
	
	var Pdata = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100];
    var Wdata = [100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1];
	*/
	
	
	// Calculate the maximum height
    const PMaxHeight = () => Math.max(...Pdata);
	const WMaxHeight = () => Math.max(...Wdata);

    // Function to create bars
    function PcreateBars() {
		const PressureChart = document.getElementById('PressureChart');
		PressureChart.innerHTML = ''; // Clear existing bars
    
		let maxHeight = PMaxHeight();
		if (maxHeight === 0 || maxHeight < 1250) {
			maxHeight = 1250;
		}
    
		Pdata.forEach(height => {
			const Pbar = document.createElement('div');
			Pbar.className = 'Pbar';
			const heightPercent = (height / maxHeight) * 100;
			Pbar.style.height = heightPercent + '%';
			PressureChart.appendChild(Pbar);
		});
    
		const markerHeights = [0.222, 0.472, 0.722, 0.972]; // Marker positions
		const markerTexts = [0.25, 0.5, 0.75, 1]; // Marker text values
	
		markerHeights.forEach((fraction, index)=> {
			const marker = document.createElement('div');
			marker.className = 'marker';
			marker.style.bottom = (fraction * 100) + '%';
			marker.innerText = (markerTexts[index] * maxHeight).toFixed(2); // Marker text as percentage
			PressureChart.appendChild(marker);
		});
	
		const thresholdMarker = document.createElement('div');
		thresholdMarker.className = 'thresholdMarker';
		threshold = Pthreshold;
		thresholdMarker.innerText = threshold;
		threshold1 = ((threshold / maxHeight) - 0.028);
		thresholdMarker.style.bottom = (threshold1 * 100) + '%';
		PressureChart.appendChild(thresholdMarker);
	}

		
	function WcreateBars() {
		const WaterChart = document.getElementById('WaterChart');
		WaterChart.innerHTML = ''; // Clear existing bars
    
		let maxHeight = WMaxHeight();
		if (maxHeight === 0 || maxHeight < 30) {
			maxHeight = 30;
		}
    
		Wdata.forEach(height => {
			height = height + maxHeight;
			const Wbar = document.createElement('div');
			Wbar.className = 'Wbar';
			const heightPercent = (height / (maxHeight * 2)) * 100;
			Wbar.style.height = heightPercent + '%';
			WaterChart.appendChild(Wbar);
		});
    
		const markerHeights = [0.222, 0.472, 0.722, 0.972]; // Marker positions as fractions of maxHeight
		const markerTexts = [-0.5, 0, 0.5, 1]; // Marker text values
    
		markerHeights.forEach((fraction, index) => {
			const marker = document.createElement('div');
			marker.className = 'marker';
			marker.style.bottom = (fraction * 100) + '%';
			marker.innerText = (maxHeight * markerTexts[index]).toFixed(2);
			WaterChart.appendChild(marker);
		});
	
	
		const thresholdMarker = document.createElement('div');
		thresholdMarker.className = 'thresholdMarker';
		threshold = Wthreshold;
		thresholdMarker.innerText = threshold;
		threshold = Wthreshold + maxHeight;
		threshold1 = (threshold / (maxHeight * 2) - 0.028);
		thresholdMarker.style.bottom = (threshold1 * 100) + '%';
		WaterChart.appendChild(thresholdMarker);
	}
	
		
		
	// Initial creation of bars
    PcreateBars();
	WcreateBars();
		
	
    function Credits() {
        alert("Credits to the following people on the Team \n \n -Rohit Medarametla \n -Aadi Madhavan \n -Avie Lal \n -Matthew Misa \n \n 'This was really fun to work with and we hope for its inovation'");
    }
	
	function showPopup() {
		document.getElementById('popupOverlay').style.display = 'block';
    }

	function closePopup() {
		document.getElementById('popupOverlay').style.display = 'none';
	}
	
	

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
			
			//Height
			Wthreshold = ((threshold - Base) * (100)) / (Density * Gravity);
			Wthreshold = Wthreshold * 100;	
			
			document.getElementById("PdisplayDiv").innerHTML = Pthreshold;
			document.getElementById("WdisplayDiv").innerHTML = Wthreshold;
		}
		
		UpdateThreshold(Pthreshold);
    
		PcreateBars();
		WcreateBars();
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
			Pthreshold = (((threshold / 100) * Density * Gravity) + (Base * 100));
			Pthreshold = (Pthreshold / 100);
			
			//height
			Wthreshold = threshold;
			
			document.getElementById("PdisplayDiv").innerHTML = Pthreshold;
			document.getElementById("WdisplayDiv").innerHTML = Wthreshold;
		}	

		UpdateThreshold(Pthreshold);
		
		PcreateBars();
		WcreateBars();
	}

	function UpdateThreshold(value) {
		var xhttp = new XMLHttpRequest();
		xhttp.open("PUT", "UPDATE_THRESHOLD?VALUE="+value, true);
		xhttp.send();
    }

	function UpdateThreshold(value) {
		var xhttp = new XMLHttpRequest();
		xhttp.open("PUT", "UPDATE_THRESHOLD?VALUE="+value, true);
		xhttp.send();
    }

    // global variable visible to all java functions
    var xmlHttp=createXmlHttpObject();

    // function to create XML object
    function createXmlHttpObject(){
		if(window.XMLHttpRequest){
			xmlHttp=new XMLHttpRequest();
		}
		
		else {
			xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");
		}
		
		return xmlHttp;
    }
	

	// Function to update pressure readings and shift previous values
	function PupdatePressureReadings(newReading) {

		result = newReading;

		// Add the new reading to the beginning of the array
		if (!isNaN(result) && result > 0) {
			Pdata.unshift(result);
			if (Pdata.length > 100) {
				Pdata.pop(); // Remove the oldest bar if there are more than 100
			}
		
		PcreateBars();
		}
	}

	function WupdatePressureReadings(newReading) {

		result = newReading;

		result = ((result - Base) * (100)) / (Density * Gravity);
		result = result * 100;
		result1 = (result).toFixed(2);
	
		document.getElementById("w0").innerHTML = result1;

		// Add the new reading to the beginning of the array
		Wdata.unshift(result);
    
		// Remove the oldest reading if the array length exceeds
		if (Wdata.length > 100) {
			Wdata.pop();
		}
		
		WcreateBars();
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
	  
		if (message > Pthreshold) {
			showPopup();
		}
	  
		PupdatePressureReadings(message);
		WupdatePressureReadings(message);	
	  
		barwidth = message / 4060;
		document.getElementById("b0").innerHTML=message;
		document.getElementById("b0").style.width=(barwidth+"%");
      
	  
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
      
		xmldoc = xmlResponse.getElementsByTagName("Alarm");
		message = xmldoc[0].firstChild.nodeValue;
		document.getElementById("A1").innerHTML=message;
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
	
	/*
	 get it? here's the xml message example:
	<?xml version="1.0" encoding="UTF-8"?>
			<Pressure>1500</Pressure>
		<data>
			<Temperature>25</Temperature>
		</data>
	*/
  
  
</script>

</html>



)=====";