document.querySelector(".correct").onclick = function() {
    this.style.backgroundColor = "green"
    document.querySelector("#feedback1").innerHTML = "Correct!";
}

document.querySelectorAll(".incorrect").forEach(function(button) {button.onclick = function(){
    this.style.backgroundColor = "red"
    document.querySelector("#feedback1").innerHTML = "Incorrect!";
    }
})

document.getElementById("check").onclick = function() {
    let answer = document.querySelector("input")
    if (answer.value == "Switzerland") {
        answer.style.backgroundColor = "green";
        document.querySelector("#feedback2").innerHTML = "Correct!";
    } else {
        answer.style.backgroundColor = "red";
        document.querySelector("#feedback2").innerHTML = "Incorrect!";
    }
}

