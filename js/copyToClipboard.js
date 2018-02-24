$(document).ready(function() {

	// copy command to clipboard button is clicked
	$("#button1").click(function() {
		var command = $("#download-cmd").text();
		$("#command1").val(command);
		$("#command1").select();
		document.execCommand("Copy");
		// $("#command1").css("display", "none");
	});

	$("#button2").click(function() {
		var command = $("#open-dir-cmd").text();
		$("#command2").val(command);
		$("#command2").select();
		document.execCommand("Copy");
	});

	$("#button3").click(function() {
		var command = $("#make-cmd").text();
		$("#command3").val(command);
		$("#command3").select();
		document.execCommand("Copy");
	});

	$("#button4").click(function() {
		var command = $("#install-cmd").text();
		$("#command4").val(command);
		$("#command4").select();
		document.execCommand("Copy");
	});
});