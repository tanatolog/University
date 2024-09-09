document.getElementById("input").addEventListener("click", function (e) {  e.preventDefault();
    var login = document.getElementById("logemail").value;
    var pass = document.getElementById("logpass").value;
    if (login != "" & pass != "") {
    let autorization = JSON.stringify({login: login, pass: pass});
    let request = new XMLHttpRequest();
    request.open("POST", "/autorization", true);   
    request.setRequestHeader("Content-Type", "application/json");
    request.addEventListener("load", function () {
        let receivedUser = JSON.parse(request.response);
        var check = receivedUser["check"];
        if (check == false) {
            document.getElementById('autorization_fall').textContent = 'Логин или пароль введены неверно.'
            document.getElementById('autorization_fall').setAttribute('class','colortext');
        }
        else {
            var token = receivedUser["token"];
            document.cookie = "authBlogBegin=" + token + 'authBlogEnd';
            var masSplit = document.cookie.split("authBlogBegin=") 
            var mas2Split = masSplit[1].split("authBlogEnd") 
            var token = mas2Split[0];
            document.location.href = 'http://localhost:3000/'
        }
    });
    request.send(autorization);
}
else {
    document.getElementById("alert").style.display = 'block';
    document.getElementById("alert").setAttribute("class", "alert alert-danger");
    document.getElementById("alert").textContent = 'Заполните все поля!';   
    window.scrollTo(0, 0);
}
});