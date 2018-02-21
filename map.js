function map() {
	var mapCenter = new google.maps.LatLng(40.4259, -86.9081);
	var properties = {
		center : mapCenter,
		zoom : 12, scrollwheel : false, draggable : false,
		mapTypeId : google.maps.mapTypeId.ROADMAP
	};
	var map = new google.maps.Map(document.getElementById("locationMap"), properties);
}