export function ValidNum(n) {
    return n || n === 0;
}

export function CompareFuzz(a, b, fuzz){
    return Math.abs(a - b) < fuzz;
}