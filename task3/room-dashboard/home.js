function change() {
    let rg_tenda = document.getElementById("rgTenda");
    let btn_Luce = document.getElementById("btnLuce");
    rg_tenda.classList.toggle("dark");
    btn_Luce.classList.toggle("dark");
    document.body.classList.toggle("dark");
    document.querySelector(".check").classList.toggle("dark");
    document.querySelector(".luce").classList.toggle("dark");
    document.querySelector(".tenda").classList.toggle("dark");
    document.querySelector("aside").classList.toggle("dark");
    let a = document.querySelectorAll("a");
    a[0].classList.toggle("dark");
    a[1].classList.toggle("dark");
    let ul = document.querySelectorAll("ul > li");
    ul[0].classList.toggle("dark");
    ul[1].classList.toggle("dark");
    if (btn_Luce.value == "ON") {
        btn_Luce.value = "OFF";
    } else {
        btn_Luce.value = "ON";
    }
}


window.addEventListener("load", function (event) {
    let checkLuce = document.querySelector("#manualLuce");
    let checkTenda = document.querySelector("#manualTenda");

    checkLuce.addEventListener("change", function (event) {
        let btn_Luce = document.getElementById("btnLuce");
        if (this.checked) {
            btn_Luce.removeAttribute("disabled", true);
        } else {
            btn_Luce.setAttribute("disabled", false);
        }
    });

    checkTenda.addEventListener("change", function (event) {
        let rg_tenda = document.getElementById("rgTenda");
        if (this.checked) {
            rg_tenda.removeAttribute("disabled", true);
        } else {
            rg_tenda.setAttribute("disabled", false);
        }
    });




});