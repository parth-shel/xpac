$(document).ready(function() {

	// copy command to clipboard button is clicked
	$("#button1").click(function() {
		var command = $("#download-cmd").text();
		console.log(command);
		dummy(command);
	});

	$("#button2").click(function() {
		var command = $("#open-dir-cmd").text();
		console.log(command);
		dummy(command);
	});

	$("#button3").click(function() {
		var command = $("#make-cmd").text();
		console.log(command);
		dummy(command);
	});

	$("#button4").click(function() {
		var command = $("#install-cmd").text();
		console.log(command);
		dummy(command);
	});

	// dummy method which creates an input field to copy text to clipboard from
	function dummy(command) {
		var dummyInput = document.createElement("input");
		document.body.appendChild(dummyInput);
		$(dummyInput).css('display', 'none');
		dummyInput.setAttribute("id", "dummy_id");
		document.getElementById("dummy_id").value = command;
		dummyInput.select();
		document.execCommand("copy");
		document.body.removeChild(dummyInput);
		console.log("Successfully copied!");
	}
});