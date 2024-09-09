function getCookie(name) {
    let matches = document.cookie.match(new RegExp(
      "(?:^|; )" + name.replace(/([\.$?*|{}\(\)\[\]\\\/\+^])/g, '\\$1') + "=([^;]*)"
    ));
    return matches ? decodeURIComponent(matches[1]) : undefined;
}

function setCookie(name, value, options = {}) {

    options = {
      path: '/',
      // при необходимости добавьте другие значения по умолчанию
      ...options
    };
  
    if (options.expires instanceof Date) {
      options.expires = options.expires.toUTCString();
    }
  
    let updatedCookie = encodeURIComponent(name) + "=" + encodeURIComponent(value);
  
    for (let optionKey in options) {
      updatedCookie += "; " + optionKey;
      let optionValue = options[optionKey];
      if (optionValue !== true) {
        updatedCookie += "=" + optionValue;
      }
    }
  
    document.cookie = updatedCookie;
}
  
function deleteCookie(name) {
    setCookie(name, "", {
      'max-age': -1
    })
  }

function page_loading() {
  ////console.log(document.cookie);
    if (getCookie("in-system") == "true") {
        const ul_nav = document.getElementById("ul-nav");
        ul_nav.removeChild(document.getElementById("delete"));
        const user_name = document.getElementById('user_name');
        user_name.innerText = getCookie("name");
    } else {
        document.getElementById("user_name_main").remove();
        const menu = document.getElementById("for-login");
        menu.childNodes.forEach(child => {
          child.className = 'list-group-item disabled';
        });
    }
    //load_blogs();
}

function logout() {
    deleteCookie("in-system");
    deleteCookie('uid');
    deleteCookie('name');
    deleteCookie('token');
    deleteCookie('role');
    window.location.replace("/");

}

function autorization(login = "", pass = "") {
    //document.getElementById("input").addEventListener("click", function (e) {  e.preventDefault();
    var login = document.getElementById("floatingInput").value;
    var pass = document.getElementById("floatingPassword").value;
        if (login != "" & pass != "") {
        let autorization = JSON.stringify({login: login, pass: pass});
        let request = new XMLHttpRequest();
        request.open("POST", "/service/autorization", true);   
        request.setRequestHeader("Content-Type", "application/json");
        request.addEventListener("load", function () {
            let receivedUser = JSON.parse(request.response);
            ////console.log(receivedUser);
            var check = receivedUser["check"];
            if (check == false) {
                document.getElementById("pass_warning").style.display = 'block';
                document.getElementById("pass_warning").setAttribute("class", "alert alert-danger");
                document.getElementById("pass_warning").textContent = "Неверный логин или пароль";
            }
            else {
                // var token = receivedUser["token"];
                // document.cookie = "authBlogBegin=" + token + 'authBlogEnd';
                // var masSplit = document.cookie.split("authBlogBegin=") 
                // var mas2Split = masSplit[1].split("authBlogEnd") 
                // var token = mas2Split[0];
                // document.location.href = 'http://localhost:3000/'
                console.log(receivedUser);
                setCookie("in-system", "true");
                setCookie("name", receivedUser.name);
                setCookie("uid", receivedUser.uid);
                setCookie("role", receivedUser.role);
                setCookie("token",receivedUser.token)
                window.location.reload();
                //window.location.replace("/lk/admin");
            }
        });
        request.send(autorization);
    }
    else {
        document.getElementById("pass_warning").style.display = 'block';
        document.getElementById("pass_warning").setAttribute("class", "alert alert-danger");
        document.getElementById("pass_warning").textContent = 'Заполните все поля!';   
        //window.scrollTo(0, 0);
    }
    //});
}

function setError(id, text) {
  document.getElementById(id).style.display = 'block';
  document.getElementById(id).setAttribute("class", "alert alert-danger my-padding");
  document.getElementById(id).textContent = text;
}

function registration(login = "", mail ="", pass = "") {
  var login = document.getElementById("sign-name").value.trim();
  var mail = document.getElementById("sign-email").value.trim();
  var pass = document.getElementById("sign-password").value;
  var pass2 = document.getElementById("sign-password2").value;
      if (login != "" & pass != "" & mail != "" & pass2 != "") {

        if (login.length > 25) {
          setError("pass_sign_warning", "Неправильное имя!");
          return;
        }

        var re=/^[а-яА-Яa-zA-Z0-9_]+@[а-яА-Яa-zA-Z_]+?\.[а-яА-Яa-zA-Z]{2,3}$/
        if (mail.length > 100 || !re.test(mail)) {
          setError("pass_sign_warning", "Неправильная почта!");
          return;
        }

        if (pass.pass > 63) {
          setError("pass_sign_warning", "Пароль должен быть < 64!");
          return;
        }

        if (pass !== pass2) {
          setError("pass_sign_warning", "Пароли не совпадают!");
          return;
        }

      let autorization = JSON.stringify({login: login, pass: pass, mail:mail});
      let request = new XMLHttpRequest();
      request.open("POST", "/service/registration", true);   
      request.setRequestHeader("Content-Type", "application/json");
      request.addEventListener("load", function () {
          let receivedUser = JSON.parse(request.response);
          var check = receivedUser["check"];
          if (check == false) {
              setError("pass_sign_warning", "Такой пользователь уже есть!");
          }
          else {
              setCookie("in-system", "true");
              setCookie("name", receivedUser.name);
              setCookie("uid", receivedUser.uid);
              setCookie("role", receivedUser.role);
              setCookie("token",receivedUser.token);
              window.location.reload();
          }
      });
      request.send(autorization);
  }
  else { 
      setError("pass_sign_warning", 'Заполните все поля!');
  }
}