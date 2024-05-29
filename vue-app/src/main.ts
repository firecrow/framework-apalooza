import './assets/main.css'

import { createApp } from 'vue'
import App from './App.vue'


declare var window:any;

class MyApp  {
    container: HTMLElement;
    constructor(container: HTMLElement){
        this.container = container;

        if(!container.hasChildNodes()){
            const root = document.createElement('angular-root');
            container.appendChild(root);
        }

        createApp(App).mount('#app')
    }
    hide(){
        this.container.classList.add('hidden');
    }
    show(){
        this.container.classList.remove('hidden');
    }
}

window.FwpVue = {App: MyApp};

