nz = {};

nz.init = function (me, to) {
    nz._me = me;
    nz._to = to;
    nz.last = "";
};

nz.initStyle = function (font, size) {
    style = document.createElement("style");
    style.type = "text/css";

    style.innerText = "body {"
    + "font-family: " + font + ";"
    + "font-size: " + size + "px;"
    + "}";

    document.head.appendChild(style);
}

nz.addOutMessage = function (message, date) {
    if (!nz._me)
	return ;

    msg = {};

    msg.parent = document.createElement("div");
    msg.parent.className = "nzMessage nzOutMessage";

    if (nz.last != nz._me) {
	msg.sender = document.createElement("div");
	msg.sender.className = "nzSender";

	msg.senderText = document.createTextNode(nz._me);
    }

    msg.msg = document.createElement("div");
    msg.msg.className = "nzMessageText";
    msg.msg.innerHTML = message;

    msg.date = document.createElement("div");
    msg.date.className = "nzTimestamp";

    msg.dateText = document.createTextNode(date);

    if (nz.last != nz._me)
	msg.sender.appendChild(msg.senderText);
    msg.date.appendChild(msg.dateText);

    if (nz.last != nz._me)
	msg.parent.appendChild(msg.sender);
    msg.parent.appendChild(msg.date);
    msg.parent.appendChild(msg.msg);

    document.body.appendChild(msg.parent);

    nz.last = nz._me;
};

nz.addInMessage = function (message, date) {
    if (!nz._me)
	return ;

    msg = {};

    msg.parent = document.createElement("div");
    msg.parent.className = "nzMessage nzInMessage";

    if (nz.last != nz._to) {
	msg.sender = document.createElement("div");
	msg.sender.className = "nzSender";

	msg.senderText = document.createTextNode(nz._to);
    }

    msg.msg = document.createElement("div");
    msg.msg.className = "nzMessageText";
    msg.msg.innerHTML = message;

    msg.date = document.createElement("div");
    msg.date.className = "nzTimestamp";

    msg.dateText = document.createTextNode(date);

    if (nz.last != nz._to)
	msg.sender.appendChild(msg.senderText);
    msg.date.appendChild(msg.dateText);

    if (nz.last != nz._to)
	msg.parent.appendChild(msg.sender);
    msg.parent.appendChild(msg.date);
    msg.parent.appendChild(msg.msg);

    document.body.appendChild(msg.parent);

    nz.last = nz._to;
};
