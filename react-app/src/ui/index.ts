import {createRoot} from "react-dom/client";
import {Layout} from "./layout";
import * as React from "react";

export class App  {
    container: HTMLElement;
    constructor(){
        let x:number = 0;
        console.log(x + 100);

        const container = document.getElementById("react-root");
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
