import {createRoot} from "react-dom/client";
import {Layout} from "./layout";
import * as React from "react";

export class App  {
    container: HTMLElement;
    constructor(container: HTMLElement){
        this.container = container;

        if(container){
            this.container = container;
            const root = createRoot(this.container);
            root.render(React.createElement(Layout, {}));
        }
    }
    hide(){
        this.container.classList.add('hidden');
    }
    show(){
        this.container.classList.remove('hidden');
    }
}
