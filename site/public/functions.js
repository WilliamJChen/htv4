const numberId = document.getElementById('numberId');
const send = document.getElementById('send');
          
const database = firebase.database();

send.addEventListener('click', (e) => {
    e.preventDefault();
    database.ref('/user/'+numberId.value).set({
        number_name: numberId.value,
    });
});