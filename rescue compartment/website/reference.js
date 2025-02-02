import { initializeApp } from 'https://www.gstatic.com/firebasejs/9.1.3/firebase-app.js';
import { getDatabase, ref as dbRef, onValue } from 'https://www.gstatic.com/firebasejs/9.1.3/firebase-database.js';
import { getStorage, ref as storageRef, listAll, getDownloadURL } from 'https://www.gstatic.com/firebasejs/9.1.3/firebase-storage.js';

const firebaseConfig = {
    apiKey: "AIzaSyAaqIvs64SGpMgVqIFDrR1yr9-Vl-cv5JA",
    authDomain: "rescuelink-748d6.firebaseapp.com",
    databaseURL: "https://rescuelink-748d6-default-rtdb.firebaseio.com",
    projectId: "rescuelink-748d6",
    storageBucket: "rescuelink-748d6.appspot.com",
    messagingSenderId: "792291380537",
    appId: "1:792291380537:web:977155d3c8acbb1465ece8"
};

const app = initializeApp(firebaseConfig);
const database = getDatabase(app);
const storage = getStorage(app);

let map, directionsService, directionsRenderer;

const urlParams = new URLSearchParams(window.location.search);

document.querySelector('.viewimages').addEventListener('click', () => {
    const username = urlParams.get('username');
    const type = urlParams.get('type');

    if (type === 'emergency') {
        const imagesRef = storageRef(storage, `${username}/`);

        const imageView = document.querySelector('.imageview');

        const images = imageView.querySelectorAll('img');

        images.forEach(img => img.remove());

        listAll(imagesRef).then((res) => {
            res.items.forEach((imageRef) => {
                getDownloadURL(imageRef).then((url) => {
                    const img = document.createElement('img');
                    img.src = url;
                    img.className = 'image';
                    document.querySelector('.imageview').appendChild(img);
                });
            });
        });

        document.querySelector('.imageview').style.visibility = "visible";
    } else {
        console.log('Type is not emergency');
    }
});

document.querySelector('.fa-xmark').addEventListener('click', () => {
    document.querySelector('.imageview').style.visibility = "hidden";
});

function initMap() {
    const initialLocation = { lat: 22.92605438273513, lng: 79.23518708062967 };

    map = new google.maps.Map(document.getElementById("map"), {
        center: initialLocation,
        zoom: 5,
        minZoom: 3,
        maxZoom: 20,
        mapTypeId: google.maps.MapTypeId.HYBRID,
        disableDefaultUI: true,
        streetViewControl: false,
        mapTypeControl: false,
        fullscreenControl: false,
    });

    directionsService = new google.maps.DirectionsService();
    directionsRenderer = new google.maps.DirectionsRenderer();
    directionsRenderer.setMap(map);

    // Check if URL contains username and type parameters
    const username = urlParams.get('username');
    const type = urlParams.get('type');

    if (username && type) {
        const userRef = dbRef(database, `users/${username}`);

        onValue(userRef, (snapshot) => {
            const userData = snapshot.val();

            if (userData) {
                document.getElementById("name").innerText = userData.name;
                document.getElementById("pnum").innerText = userData.phone_number;
                document.getElementById("ppnum").innerText = userData.parents_phone_number;
                document.querySelector(".shinf").style.visibility = "visible";
            }
        });

        const markerRef = dbRef(database, `${type}/${username}/position`);
        onValue(markerRef, (snapshot) => {
            const data = snapshot.val();
            if (data) {
                const position = data;
                const marker = new google.maps.Marker({
                    position: { lat: position.latitude, lng: position.longitude },
                    map: map,
                    icon: {
                        url: "http://maps.google.com/mapfiles/ms/icons/blue-dot.png",
                        scaledSize: new google.maps.Size(40, 40)
                    },
                    title: username
                });

                // Create route from current location to marker location
                if (navigator.geolocation) {
                    navigator.geolocation.getCurrentPosition(position => {
                        const currentPosition = {
                            lat: position.coords.latitude,
                            lng: position.coords.longitude
                        };

                        const request = {
                            origin: currentPosition,
                            destination: marker.getPosition(),
                            travelMode: google.maps.TravelMode.WALKING
                        };

                        directionsService.route(request, (result, status) => {
                            if (status === google.maps.DirectionsStatus.OK) {
                                directionsRenderer.setDirections(result);
                            }
                        });
                    }, error => {
                        console.error("Error getting current location:", error);
                    });
                } else {
                    console.log("Geolocation is not supported by this browser.");
                }
            }
        });
    } else {
        // Create all markers
        addMarkers();
    }
}

function addMarkers() {
    console.log("Add tracking marker");
    const emergencyRef = dbRef(database, 'emergency');
    const pplindisaterRef = dbRef(database, 'pplindisater');

    console.log("ok");

    onValue(emergencyRef, (snapshot) => {
        const data = snapshot.val();
        for (const key in data) {
            const position = data[key].position;
            const marker = new google.maps.Marker({
                position: { lat: position.latitude, lng: position.longitude },
                map: map,
                icon: {
                    url: "http://maps.google.com/mapfiles/ms/icons/orange-dot.png",
                    scaledSize: new google.maps.Size(40, 40)
                },
                title: key
            });

            google.maps.event.addListener(marker, 'click', () => {
                window.location.href = `?username=${key}&type=emergency`;
            });
        }
    });

    onValue(pplindisaterRef, (snapshot) => {
        const data = snapshot.val();
        for (const key in data) {
            const position = data[key].position;
            const marker = new google.maps.Marker({
                position: { lat: position.latitude, lng: position.longitude },
                map: map,
                icon: {
                    url: "http://maps.google.com/mapfiles/ms/icons/blue-dot.png",
                    scaledSize: new google.maps.Size(40, 40)
                },
                title: key
            });

            google.maps.event.addListener(marker, 'click', () => {
                window.location.href = `?username=${key}&type=disasterzone`;
            });
        }
    });
}

window.initMap = initMap;