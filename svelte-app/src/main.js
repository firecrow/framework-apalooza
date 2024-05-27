import App  from './App.svelte';

export class SvelteApp  {
    container;
    constructor(container){
        this.container = container;
        const app = new App({
            target: container,
            props: {
                name: 'svelte-app'
            }
        });
    }
    hide(){
        this.container.classList.add('hidden');
    }
    show(){
        this.container.classList.remove('hidden');
    }
}

const wrapper = {
    App:SvelteApp
}

export default wrapper;
