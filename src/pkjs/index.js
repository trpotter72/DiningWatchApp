// Function to send a message to the Pebble using AppMessage API
// We are currently only sending a message using the "status" appKey defined in appinfo.json/Settings

/*
function sendStatus(val) {
	Pebble.sendAppMessage({"status": val}, messageSuccessHandler, messageFailureHandler);
}

// Called when the message send attempt succeeds
function messageSuccessHandler() {
  console.log("Message send succeeded.");  
}

// Called when the message send attempt fails
function messageFailureHandler() {
  console.log("Message send failed.");
  sendStatus(1);
}

// Called when JS is ready
Pebble.addEventListener("ready", function(e) {
  console.log("JS is ready!");
  sendStatus(1);
});
												
// Called when incoming message from the Pebble is received
// We are currently only checking the "message" appKey defined in appinfo.json/Settings
Pebble.addEventListener("appmessage", function(e) {
	var dict = e.payload;
	console.log("Message heard from phone... analyzing dictionary\n" + "status: " + dict.status + "\nrequestmenu: " + dict.requestmenu + "\nmenudata: " + dict.menudata + "\nmenusize: "+ dict.menusize );
	if(dict['requestmenu']){
		console.log("Received Message: " + dict.requestmenu);
		sendMenuData("DaisyHillGrill,Food1,Food2,Food3,!BBQ Land,Food1,Food2,!");
	}
  
	if(dict['menudata']||dict['menusize']||dict['status']){
		console.log("Watch sent an invlaid  KEY ");
	}
});



*/
//
//
///
///

//GAGE

///
///
//
//

var menuURL = "https://dept.ku.edu/~union/cgi-bin/wordpress/dining-menus/ku-dining-menus.php?";
var method = "GET";

//constructs the current date for the request's URL
var today = new Date();
var day = today.getDate();
var dayOfWeek = today.getDay();
var weekendBool = (dayOfWeek === 0 || dayOfWeek === 6);
var month = (today.getMonth() + 1);
var year = today.getFullYear();
var dateURL = "&eventdate=" + month + "%2F" + day + "%2F" + year; 

//constructs the final url from different perameters
var diningCenter = "EKDAHL+DINING";
var diningCenterURL = "service_unit=" + diningCenter;
var URL = menuURL + diningCenterURL + dateURL; //final url for request

//Counters for station and item numbers
var stations = 0;
var foods = [];

//seperate menus and sorter function
var menuBreakfast = [];
var menuBrunch = [];
var menuLunch = [];
var menuDinner = [];
var mealSort = function(menu)
{
	var BreakIter = 0;
	var BrunchIter = 0;
	var LunchIter = 0;
	var DinnerIter = 0;
	if(weekendBool)
	{	//Weekend Condition
		for(var i = 0; i < menu.length; i++)
		{
			if(menu[i][3] == "BRUNCH")
			{
				menuBrunch[BrunchIter] = [
					menu[i][5],
					menu[i][7]
				];
				BrunchIter++;
			}
			else if(menu[i][3] == "DINNER    ")
			{
				menuDinner[DinnerIter] = [
					menu[i][5],
					menu[i][7]
				];
				DinnerIter++;
			}
		}
		console.log(menuDinner);
	}
	else
	{	//Weekday Condition
		for(var j = 0; j < menu.length; j++)
		{
			if(menu[j][3] == "BREAKFAST ")
			{
				menuBreakfast[BreakIter] = [
					menu[j][5],
					menu[j][7]
				];
				BreakIter++;
			}
			else if(menu[j][3] == "LUNCH     ")
			{
				menuLunch[LunchIter] = [
					menu[j][5],
					menu[j][7]
				];
				LunchIter++;
			}
			else if(menu[j][3] == "DINNER    ")
			{
				menuDinner[DinnerIter] = [
					menu[j][5],
					menu[j][7]
				];
				DinnerIter++;
			}
		}
	}
	menuBreakfast = JSON.stringify(arrayToString(menuBreakfast));
	menuBrunch = JSON.stringify(arrayToString(menuBrunch));
	menuLunch = JSON.stringify(arrayToString(menuLunch));
	menuDinner = JSON.stringify(arrayToString(menuDinner));
};

function arrayToString(m)
{
	var stationIndex = 0; //for setting foods to the next index
	var menuString = "";
	menuString = m[0][0] + "," + m[0][1];
	for(var l = 1; l < m.length; l++)
	{
		if(m[l][0] == m[l - 1][0])
		{
			menuString = menuString + "," + m[l][1];
			foods[stationIndex]++;
		}
		else
		{
			menuString = menuString + "!" + m[l][0] + "," + m[l][1];
			stations++;
			stationIndex++;
		}		
	}
	return(menuString);
}

console.log("Request URL: " + URL);

//Converts the menu data into JSON
var dataFormatting = function(data)
{
	data = JSON.parse(data);
	mealSort(data);
};

// Create the request
var menuRequest = new XMLHttpRequest();

//Callback for when the request is completed
menuRequest.onload = function() {
	console.log("Got unsorted response:", this.responseText);
	dataFormatting(this.responseText);
	console.log("Formatted and Trimmed response:", menuDinner);
};

//Dictionary initialization for BT transfers

/*
var dict = {
	"status": 0,
	"requestMenu": 0,
	"menuData": "",
	"menuSize": 0,
	"weekend": 0
};
*/

var whichMeal = function(dictionary)
{
	if(dictionary.requestMenu === 0) //Statements assign menu contents
	{
		return(menuBreakfast);
	}
	else if(dictionary.requestMenu == 1)
	{
		return(menuBrunch);
	}
	else if(dictionary.requestMenu == 2)
	{
		return(menuLunch);
	}
	else if(dictionary.requestMenu == 3)
	{
		return(menuDinner);
	}
};
function findMenuSize(menu)
{
	var stringLength = [stations];
	for(var m = 0; m < foods.length; m++)
	{
		stringLength[m + 1] = foods[m];
	}
	return(stringLength);
}
//Listen for when the app is opened and then...
Pebble.addEventListener('ready', function() {
	
	Pebble.sendAppMessage({'status': 1});
	Pebble.sendAppMessage({'weekend': weekendBool});	//sends T/F for weekend
	// Send the request for the full menu
	menuRequest.open(method, URL);
	console.log("The request has been sent");
	menuRequest.send();

});
//Listen for the meal selection
Pebble.addEventListener('appmessage', function(e) {
	// Get the dictionary from the message
	var dict = e.payload;
	console.log('Got message: ' + JSON.stringify(dict));
	Pebble.sendAppMessage({'menuData': whichMeal(dict),		//Sends corret menu
						   'menuSize': findMenuSize(whichMeal(dict))	//and length of correct menu
						  });
});