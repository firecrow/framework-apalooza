"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.ReactApp = void 0;
const client_1 = require("react-dom/client");
const layout_1 = require("./layout");
const React = require("react");
class ReactApp {
    constructor() {
        let x = 0;
        console.log(x + 100);
        const container = document.getElementById("react-root");
        if (container) {
            this.container = container;
            const root = (0, client_1.createRoot)(this.container);
            root.render(React.createElement(layout_1.Layout, {}));
        }
    }
    hide() {
        this.container.classList.add('hidden');
    }
    show() {
        this.container.classList.remove('hidden');
    }
}
exports.ReactApp = ReactApp;
