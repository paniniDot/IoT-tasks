//funzione che controlla se è abilitato il controllo manuale
/*function enable() {
    let manual = document.getElementById("chkManual").checked;
    let btn_luce = document.getElementsByTagName("button");
    let rg_tenda = document.getElementsByClassName("range");
    if (manual == true) {
        //il bottone e il range si devono abilitare
        let a = btn_luce.removeAttr("disabled");
        let b = rg_tenda.removeAttr("disabled");
        console.log(a);
        console.log(b);
    } else {
        //tutto disabilitato
        let a = btn_luce.attr('disabled', 'disabled');
        let b = rg_tenda.attr('disabled', 'disabled');
        console.log(a);
        console.log(b);
    }
}*/

function change() {
    let rg_tenda = document.getElementById("rgTenda");
    let btn_Luce = document.getElementById("btnLuce");
    rg_tenda.classList.toggle("dark");
    btn_Luce.classList.toggle("dark");
    document.body.classList.toggle("dark");
    // capire come cambiare lo stile alle altre cose
}