# Schéma de câblage partie puissance

```ascii
Secteur 230V AC          SSR              Résistance
┌───────────┐          ┌─────┐           ┌─────────┐
│    L      ├──────┬───┤L1   │           │         │
│           │      │   │     ├───────────┤         │
│           │      │   │     │           │         │
│    N      ├──────┼───┤L2   │           │         │
│           │      │   └─────┘           │         │
│           │      └───────────────────┬─┤         │
│    PE     ├────────────────────────┬─┼─┤         │
└───────────┘                        │ │ └─────────┘
                                    │ │
                              ┌─────┴─┴──────┐
                              │   Cuve       │
                              └──────────────┘

Notes:
- Disjoncteur différentiel 30mA en amont
- Fils minimum 2.5mm²
- Fusible calibré pour la résistance
- Doigt de gant pour la sonde de température
- Boîtier séparé pour la partie puissance
```
