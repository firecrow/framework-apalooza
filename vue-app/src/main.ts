import { createApp } from 'vue'
import App from './App.vue'


declare var window:any;

class MyApp  {
    container: HTMLElement;
    constructor(container: HTMLElement){
        this.container = container;

        if(!container.id){
            container.id = 'vue-root'
        }

        console.log('mounting Vue');
        createApp(App).mount('#vue-root')
    }
    hide(){
        this.container.classList.add('hidden');
    }
    show(){
        this.container.classList.remove('hidden');
    }
}

window.FwpVue = {App: MyApp};

