var button = document.getElementById('mainButton');

var openForm = function() {
    button.className = 'active';
};

var checkInput = function(input) {
    if (input.value.length > 0) {
        input.className = 'active';
    } else {
        input.className = '';
    }
};

var closeForm = function() {
    button.className = '';
};

document.addEventListener("keyup", function(e) {
    if (e.keyCode == 27 || e.keyCode == 13) {
        closeForm();
    }
});

var attempt = 3; // Variable to count number of attempts.
// Below function Executes on click of login button.
function validate() {
    var username = document.getElementById("username").value;
    var password = document.getElementById("password").value;
    if (username == "admin" && password == "1234") {
        alert("Login successfully");
        window.location = "/PowerTimestamps/Index"; // Redirecting to other page.
        return false;

    } else {
        attempt--; // Decrementing by one.
        alert("You have left " + attempt + " attempt;");
        // Disabling fields after 3 attempts.
        if (attempt == 0) {
            document.getElementById("username").disabled = true;
            document.getElementById("password").disabled = true;
            document.getElementById("submit").disabled = true;
            return false;
        }
    }
}

