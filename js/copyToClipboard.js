$(document).ready(function() {

	// copy command to clipboard button is clicked
	$("#button1").click(function() {
		var command = $("#download-cmd").text();
		$("#command1").val(command);
		console.log(command);
	});

	$("#button2").click(function() {
		var command = $("#open-dir-cmd").text();
		$("#command2").val(command);
		console.log(command);
	});

	$("#button3").click(function() {
		var command = $("#make-cmd").text();
		$("#command3").val(command);
		console.log(command);
	});

	$("#button4").click(function() {
		var command = $("#install-cmd").text();
		$("#command4").val(command);
		console.log(command);
	});
});