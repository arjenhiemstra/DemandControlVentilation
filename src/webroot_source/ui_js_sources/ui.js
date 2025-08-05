var debug = true;
var websocketServerLocation = location.protocol.indexOf("https") > -1 ? 'wss://' + window.location.hostname + ':8000/ws' : 'ws://' + window.location.hostname + ':8000/ws';

let messageQueue = [];
let connectTimeout, pingTimeout;
let websock;

function startWebsock(websocketServerLocation) {
    messageQueue = [];
    clearTimeout(connectTimeout);
    clearTimeout(pingTimeout);
    pingTimeout = !1;
    connectTimeout = setTimeout((() => {
        if (debug) console.log("websock connect timeout."),
            //websock.close(),
            startWebsock(websocketServerLocation);
    }), 1000);
    websock = null;
    websock = new WebSocket(websocketServerLocation);

    websock.addEventListener('open', function (event) {
        if (debug) console.log('websock open');
        clearTimeout(connectTimeout);
        if (lastPageReq !== "") {
            update_page(lastPageReq);
        }
    });
    websock.addEventListener('message', function (event) {
        "pong" == event.data ? (clearTimeout(pingTimeout),
            pingTimeout = !1) : messageQueue.push(event.data);
    });
    websock.addEventListener('close', function (event) {
        if (debug) console.log('websock close');
    });
    websock.addEventListener('error', function (event) {
        if (debug) console.log("websock Error!", event);
        startWebsock(websocketServerLocation);
    });
    setInterval((() => {
        pingTimeout || websock.readyState != WebSocket.OPEN || (pingTimeout = setTimeout((() => {
            if (debug) console.log("websock ping timeout.");
            startWebsock(websocketServerLocation);
        }
        ), 6e4),
            websock_send("ping"))
    }
    ), 5.5e4)
}

//handle menu collapse on smaller screens
window.onload = function () {
    (function (window, document) {
        var layout = document.getElementById('layout'),
            menu = document.getElementById('menu'),
            menuLink = document.getElementById('menuLink'),
            content = document.getElementById('main');
        function toggleClass(element, className) {
            var classes = element.className.split(/\s+/),
                length = classes.length,
                i = 0;
            for (; i < length; i++) {
                if (classes[i] === className) {
                    classes.splice(i, 1);
                    break;
                }
            }
            if (length === classes.length) {
                classes.push(className);
            }
            element.className = classes.join(' ');
        }
        function toggleAll(e) {
            var active = 'active';
            e.preventDefault();
            toggleClass(layout, active);
            toggleClass(menu, active);
            toggleClass(menuLink, active);
        }
        menuLink.onclick = function (e) {
            toggleAll(e);
        };
        content.onclick = function (e) {
            if (menu.className.indexOf('active') !== -1) {
                toggleAll(e);
            }
        };
    }(this, this.document));
};


$(document).ready(function () {
    startWebsock(websocketServerLocation);
    $('#main').append(systemstatus);
    //handle menu clicks
    $(document).on('click', 'ul.pure-menu-list li a', function (event) {
        var page = $(this).attr('href');
        console.log("click catched: " + page);
        update_page(page);
        $('li.pure-menu-item').removeClass("pure-menu-selected");
        $(this).parent().addClass("pure-menu-selected");
        event.preventDefault();
    });
    $(document).on('click', '#headingindex', function (event) {
        update_page('index');
        $('li.pure-menu-item').removeClass("pure-menu-selected");
        event.preventDefault();
    });

});

function websock_send(message) {
    if (websock.readyState === 1) {
        if (debug) console.log(message);
        websock.send(message);
    }
    else {
        if (debug) console.log("websock.readyState != open");
    }
}

(async function processMessages() {
    while (messageQueue.length > 0) {
        const message = messageQueue.shift();
        processMessage(message);
    }
    await new Promise(resolve => setTimeout(resolve, 0));
    processMessages();
})();

function processMessage(message) {
    if (debug) console.log(message);
    let f;
    try {
        f = JSON.parse(decodeURIComponent(message));
    } catch (error) {
        f = JSON.parse(message);
    }
    processElements(f);
}

function processElements(x) {
    for (var key in x) {
        if (x.hasOwnProperty(key)) {
            if (Array.isArray(x[key])) {
                x[key] = JSON.stringify(x[key]);
            }
            var el = $(`#${key}`);
            if (el.is('input') || el.is('select')) {
                if ($(`#${key}`).val() !== x[key]) {
                    $(`#${key}`).val(x[key]);
                }
            }
            else if (el.is('span')) {
                if ($(`#${key}`).text() !== x[key]) {
                    $(`#${key}`).text(x[key]);
                }
            }
            else if (el.is('a')) {
                $(`#${key}`).attr("href", x[key]);
            }
            else {
                var radios = $(`input[name='option-${key}']`);
                if (radios[1]) {
                    if (radios.is(':checked') === false) {
                        radios.filter(`[value='${x[key]}']`).prop('checked', true);
                    }
                    radio(key, x[key]);
                }
            }
            var elbyname = $(`[name='${key}']`).each(function () {
                if ($(this).is('span')) {
                    if ($(this).text() !== x[key]) {
                        $(this).text(x[key]);
                    }
                }
            });
        }
    }
}


//function to load html main content
var lastPageReq = "";
function update_page(page) {
    lastPageReq = page;
    $('#main').empty();
    $('#main').css('max-width', '768px')
    if (page == 'systemstatus') { $('#main').append(systemstatus); }
    if (page == 'settings') { $('#main').append(settings); }
    if (page == 'valvecontrol') { $('#main').append(valvecontrol); }
    if (page == 'sensorconfig') { $('#main').append(sensorconfig); }
    if (page == 'statemachine') { $('#main').append(statemachine); }
    if (page == 'web_serial') { $('#main').append(web_serial); }
}

function getSettings(val) {
    if (websock.readyState === 1) {
        websock_send('{"' + val + '":true}');
    }
    else {
        if (debug) console.log("websock not open");
        setTimeout(getSettings, 250, val);
    }
}
