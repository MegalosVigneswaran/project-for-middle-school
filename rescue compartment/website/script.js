import { initializeApp } from 'https://www.gstatic.com/firebasejs/9.1.3/firebase-app.js';
import { getDatabase, ref as dbRef, onValue } from 'https://www.gstatic.com/firebasejs/9.1.3/firebase-database.js';

const firebaseConfig = {
apiKey: "AIzaSyCPD4GrinCLI27AJAjRhizdv5wYf9iIwb8",
authDomain: "quake-portal.firebaseapp.com",
databaseURL: "https://quake-portal-default-rtdb.firebaseio.com",
projectId: "quake-portal",
storageBucket: "quake-portal.firebasestorage.app",
messagingSenderId: "891129117026",
appId: "1:891129117026:web:b94a8c4343c2ec4705543b"
};

const app = initializeApp(firebaseConfig);
const database = getDatabase(app);

const map = L.map('map');
map.setView([20.5937, 78.9629], 5)

L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
    attribution: '&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors'
}).addTo(map);

onValue(dbRef(database,"/"), (snapshot) => {
    const data = snapshot.val();
    for (const key in data) {
        const lat = data[key].lat;
        const lng = data[key].lng;
        const marker = L.marker([lat,lng]).addTo(map);

        marker.on('click' , function(){
            map.setView([lat,lng],14);
        })
    }
});