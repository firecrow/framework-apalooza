function Vis_Init(){
    class Svg {
        el; 
        constructor(){
            this.el = document.createElementNS("http://www.w3.org/2000/svg", 'svg');
        }
        appendTo(parent){
            parent.appendChild(this.el);
        }
    }
    return {
        Svg: Svg
    }
};