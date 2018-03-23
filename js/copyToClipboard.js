$(document).ready(function() {
	if(!ClipboardJS.isSupported()) {// hide copy-to-clipboard buttons
		$("#button1").hide();
		$("#button2").hide();
		$("#button3").hide();
		$("#button4").hide();
	}
	
	// create an instance of ClipboardJS
	var clipboard = new ClipboardJS('.btn');
});