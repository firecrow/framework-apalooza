import {createRoot} from "react-dom/client";
import {Layout} from "./ui-react/layout";
import * as React from "react";

export class ReactApp  {
    container: HTMLElement ;
    constructor(){
        let x:number = 0;
        console.log(x + 100);

        this.container = document.getElementById("react-root");
        const root = createRoot(this.container);
        root.render(React.createElement(Layout, {}));
    }
    hide(){
        this.container.classList.add('hidden');
    }
    show(){
        this.container.classList.remove('hidden');
    }
}

export class VueApp {
    constructor(){
        console.log('Yay Vue');
    }
    hide(){
    }
    show(){
    }
}

export class SvelteApp {
    constructor(){
        console.log('Yay Svelte');
    }
    hide(){
    }
    show(){
    }
}

export class AngularApp {
    constructor(){
        console.log('Yay Angular');
    }
    hide(){
    }
    show(){
    }
}